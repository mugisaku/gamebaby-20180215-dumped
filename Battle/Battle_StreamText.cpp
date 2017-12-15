#include"Battle.hpp"




namespace gmbb{


namespace{


constexpr int  cols = 25;
constexpr int  rows =  4;


SawtoothCharacterBuffer
sc_buffer(cols,rows);


bool
stopping;


class
CommentaryWindow: public Window
{
public:
  CommentaryWindow(): Window(rect_of_versatile_window)
  {
  }


  void  render(Image&  dst, Point  offset) const noexcept override
  {
    Window::render(dst,offset);

    offset += get_base_point();

    offset.x += 8;
    offset.y += 8;

      for(auto  s: sc_buffer)
      {
        dst.print(s,offset,sys::glset);

        offset.y += 16;
      }
  }

} comment_window;


void
step() noexcept
{
  auto  pressing = ctrl.is_p_button_pressing();

    if(sys::char_buffer.is_remaining())
    {
        if(stopping)
        {
            if(pressing)
            {
              sc_buffer.rotate();

              stopping = false;
            }
        }

      else
        {
          auto  now = ctrl.get_time();

            if(now >= tmp::next_time)
            {
              tmp::next_time = now+40;

                if(sc_buffer.is_full())
                {
                  stopping = true;
                }

              else
                {
                  auto  c = sys::char_buffer.pop();

                  sc_buffer.push(c);
                }
            }
        }
    }

  else
    {
        if(pressing)
        {
          coprocesses::pop();
        }
    }
}


void
initialize() noexcept
{
  sys::root_task.push(comment_window);
}


}


const Rectangle
rect_of_versatile_window(0,160,8*(cols+2),16*(rows+1));


void
clear_stream_text() noexcept
{
  sc_buffer.reset();
}


void
terminate_stream_text() noexcept
{
  sys::root_task.erase(comment_window);
}


const coprocess
coprocess_of_stream_text("stream text",initialize,step);


}




