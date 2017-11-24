#include"Battle.hpp"
#include"SystemData.hpp"
#include"SavedData.hpp"




namespace gmbb{


namespace{


FixedString
label("battle");


constexpr int  cols = 26;
constexpr int  rows =  5;


SawtoothCharacterBuffer
sc_buffer(cols,rows);


LinearCharacterBuffer
lc_buffer(1024);


class
CommentaryWindow: public Window
{
public:
  CommentaryWindow(): Window(8*(cols+2),16*(rows+1),Point(32,140))
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
        dst.print(s,offset,system_data::glset);

        offset.y += 16;
      }
  }

} comment_window;


class
MonitorWindow: public Window
{
public:
  MonitorWindow(): Window(8*20,16*6,Point(128,144)){}

  void  render(Image&  dst, Point  offset) const noexcept override
  {
    Window::render(dst,offset);

    offset += get_base_point();

    offset.x += 8;
    offset.y += 8;

    StringBuffer  sbuf;


    dst.print("NAME      HP  MP",offset,system_data::glset);


    auto&  ch = saved_data::characters[0];

    dst.print(ch.name,offset.move_y(16),system_data::glset);
    dst.print(sbuf("%4d %3d",ch.hp,ch.mp),offset.move_x(8*8),system_data::glset);
  }

} monitor_window;


void
step(const Controller&  ctrl) noexcept
{
    if(lc_buffer.is_remaining())
    {
      auto  c = lc_buffer.pop();

      sc_buffer.push(c);
    }
}


}


void
start_battle(coreturn_t  ret) noexcept
{
  lc_buffer.push("まものが　あらわれた");

  system_data::root_task.push(monitor_window);
  system_data::root_task.push(comment_window);

  push_routine(label.pointer,step,ret);
}


}




