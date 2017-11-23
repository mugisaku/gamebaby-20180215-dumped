#include"Battle.hpp"
#include"SystemData.hpp"
#include"SavedData.hpp"




namespace gmbb{


namespace{


FixedString
label("battle");


//MessageWindow
//message_window(system_data::glset,20,6,Point(0,160));


Window
message_window;


class
MonitorWindow: public Window
{
public:
  MonitorWindow(): Window(8*20,16*5,Point(128,160)){}

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
}


}


void
start_battle(coreturn_t  ret) noexcept
{
  system_data::root_task.push(monitor_window);
  system_data::root_task.push(message_window);

  push_routine(label.pointer,step,ret);
}


}




