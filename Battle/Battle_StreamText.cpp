#include"Battle.hpp"




namespace{


constexpr int  cols = 25;
constexpr int  rows =  4;


gbstd::text_roll
text_roll(cols,rows);


bool
stopping;


class
CommentaryWindow: public gbstd::window
{
public:
  CommentaryWindow(): window(rect_of_versatile_window)
  {
  }


  void  render(gbstd::image&  dst, gbstd::point  offset) const noexcept override
  {
    window::render(dst,offset);

    offset += get_base_point();

    offset.x += 8;
    offset.y += 8;

      for(auto  s: text_roll)
      {
        dst.print(s,offset,sys::font);

        offset.y += 16;
      }
  }

} comment_window;


void
step(uint32_t&  pc) noexcept
{
    if(!pc)
    {
      sys::root_task.push(comment_window);

      ++pc;
    }


  auto  pressing = gbstd::ctrl.is_p_button_pressing();

    if(sys::text_buffer.is_remaining())
    {
        if(stopping)
        {
            if(pressing)
            {
              text_roll.rotate();

              stopping = false;
            }
        }

      else
        {
          auto  now = gbstd::ctrl.get_time();

            if(now >= tmp::next_time)
            {
              tmp::next_time = now+20;

                if(text_roll.is_full())
                {
                  stopping = true;
                }

              else
                {
                  auto  c = sys::text_buffer.pop();

                  text_roll.push(c);
                }
            }
        }
    }

  else
    {
        if(pressing)
        {
          gbstd::playworks::pop();
        }
    }
}


}


const gbstd::rectangle
rect_of_versatile_window(0,160,8*(cols+2),16*(rows+1));


void
clear_stream_text() noexcept
{
  sys::text_buffer.reset();

  text_roll.reset();
}


void
terminate_stream_text() noexcept
{
  sys::root_task.erase(comment_window);
}


const gbstd::playwork
playwork_of_stream_text("stream text",step);




