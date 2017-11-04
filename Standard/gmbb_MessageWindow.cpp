#include"gmbb_MessageWindow.hpp"
#include"gmbb_environment.hpp"
#include"gmbb_unicode.hpp"
#include<cctype>




namespace gmbb{


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


namespace{
void
scan(char*  dst, char const*&  src, size_t  n) noexcept
{
    while(n > 1)
    {
      auto  c = *src++;

        if(c == ')')
        {
          break;
        }

      else
        {
          *dst++ = c;

          --n;
        }
    }


  *dst = 0;
}
}


void
MessageWindow::
push(char const*  s, bool  with_newline)
{
  auto  tail = get_buffer_tail();

    while(*s && (input_pointer < tail))
    {
        if(*s == '$')
        {
          ++s;

            if(*s == '$')
            {
              *input_pointer++ = *s++;
            }

          else
            if(*s == '(')
            {
              char  buf[256];

              scan(buf,++s,sizeof(buf));

              push(environment::get_value(buf).data(),false);
            }

          else
            {
              *input_pointer++ = *s++;
            }
        }

      else
        {
          *input_pointer++ = *s++;
        }
    }


    if(with_newline)
    {
        if(input_pointer < tail)
        {
          *input_pointer++ = '\n';
        }
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
    }
}


void
MessageWindow::
step()
{
    if(!text.is_full() && *output_pointer)
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




