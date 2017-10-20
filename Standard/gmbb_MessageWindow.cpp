#include"gmbb_MessageWindow.hpp"
#include"gmbb_environment.hpp"
#include"gmbb_unicode.hpp"
#include<cctype>




namespace gmbb{


MessageWindow::
MessageWindow(GlyphSet&  glset, int  column_number, int  row_number, Point  pt) noexcept:
Window(glset.get_width( )*column_number+16,glset.get_height()*row_number+16,pt),
glyphset(&glset),
text(column_number,row_number),
input_pointer( buffer),
output_pointer(buffer)
{
  Window::set_state(WindowState::open_to_down);

  coloring[1] = white;
}




namespace{
char16_t*
copy(const char16_t*  src, char16_t*  dst, const char16_t*  const dst_end) noexcept
{
    if(dst == dst_end)
    {
      return dst;
    }


    while(dst < dst_end)
    {
      auto  c = *src++;

        if(!c)
        {
          break;
        }


      *dst++ = c;
    }


  *dst = 0;

  return dst;
}


int
sscan_id(const char16_t*  s, char16_t*  buf, size_t  n) noexcept
{
  int  r = 0;

    if(!n)
    {
      return 0;
    }


    if(n == 1)
    {
      *buf = 0;

      return 0;
    }


  auto  c = *s++;

    if(isalpha(c) || (c == '_'))
    {
      *buf++ = c;

      --n;
      ++r;

        for(;;)
        {
            if(n == 1)
            {
              break;
            }


          c = *s++;

            if(isalnum(c) || (c == '_'))
            {
              *buf++ = c;

              --n;
              ++r;
            }

          else
            {
              break;
            }
        }
    }


  *buf = 0;

  return r;
}
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
   input_pointer = buffer;
  output_pointer = buffer;
}


void
MessageWindow::
push(char const*  s)
{
    while((input_pointer < std::end(buffer)) && *s)
    {
      auto  byte_number = utf8_byte_number(*s);

      auto  c = to_char32(s,byte_number);

      s += byte_number;

      *input_pointer++ = c;
    }
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
step()
{
    if(output_pointer != input_pointer)
    {
        if(!text.is_full())
        {
          text.push(*output_pointer++);
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




