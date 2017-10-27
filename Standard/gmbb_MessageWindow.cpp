#include"gmbb_MessageWindow.hpp"
#include"gmbb_environment.hpp"
#include"gmbb_unicode.hpp"
#include<cctype>




namespace gmbb{


struct
MessageWindow::
ListNode
{
  std::string  name;

  void  (*callback)();

  ListNode*  previous=nullptr;
  ListNode*      next=nullptr;

  ListNode(std::string const&  name_, void  (*cb)()) noexcept:
  name(name_), callback(cb){}

};


MessageWindow::
MessageWindow(GlyphSet&  glset, int  column_number, int  row_number, Point  pt) noexcept:
Window(glset.get_width( )*column_number+16,glset.get_height()*row_number+16,pt),
glyphset(&glset),
text(column_number,row_number)
{
  reset();

  Window::set_state(WindowState::open_to_down);

  coloring[1] = white;
}




namespace{
bool  islower(char  c) noexcept{return((c >= 'a') && (c <= 'z'));}
bool  isupper(char  c) noexcept{return((c >= 'A') && (c <= 'Z'));}
bool  isalpha(char  c) noexcept{return(isupper(c) || islower(c));}
bool  isdigit(char  c) noexcept{return((c >= '0') && (c <= '9'));}
bool  isalnum(char  c) noexcept{return(isalpha(c) || isdigit(c));}

bool  isident0(char  c) noexcept{return(isalpha(c) || (c == '_'));}
bool  isidentn(char  c) noexcept{return(isalnum(c) || (c == '_'));}
}




void
MessageWindow::
clear() noexcept
{
  text.clear();

  reset();
}


void
MessageWindow::
reset() noexcept
{
  input_pointer  = buffer;
  output_pointer = buffer;

  buffer[0] = 0;
}


void
MessageWindow::
push(char const*  s)
{
  auto  tail = get_buffer_tail();

    while(*s && (input_pointer < tail))
    {
      *input_pointer++ = *s++;
    }


  *input_pointer = 0;
}


void
MessageWindow::
push(std::initializer_list<char const*>  ls)
{
    for(auto  s: ls)
    {
      push(s);

      push("\n");
    }
}


void
MessageWindow::
call(std::string const&  name) const noexcept
{
  auto  cur = list_node;

    while(cur)
    {
        if(cur->name == name)
        {
          cur->callback();

          return;
        }


      cur = cur->next;
    }
}


void
MessageWindow::
push_callback(std::string const&  name, void  (*cb)()) noexcept
{
    if(cb)
    {
      auto  nd = new ListNode(name,cb);

        if(list_node)
        {
          nd->next = list_node               ;
                     list_node->previous = nd;
        }


      list_node = nd;
    }
}


void
MessageWindow::
step()
{
    if(!text.is_full() && *output_pointer)
    {
        if(*output_pointer == '$')
        {
          ++output_pointer;

            if(*output_pointer == '$')
            {
              text.push(*output_pointer++);
            }

          else
            if(isident0(*output_pointer))
            {
              std::string  name;

              name.reserve(80);

                while(isidentn(*output_pointer))
                {
                  name += *output_pointer++;
                }


              call(name);
            }
        }

      else
        {
          auto  byte_number = utf8_byte_number(*output_pointer);

            if((output_pointer+byte_number) <= get_buffer_tail())
            {
              auto  c = to_char32(output_pointer,byte_number);

              output_pointer += byte_number;

              text.push(c);
            }
        }
    }
}


void
MessageWindow::
scroll()
{
  text.rotate();
}


void
MessageWindow::
render(Image&  dst, Point  offset) const noexcept
{
  Window::render(dst,offset);

    if(Window::get_state() == WindowState::full_opened)
    {
      text.render(dst,get_base_point()+offset+8,*glyphset,coloring);
    }
}




}




