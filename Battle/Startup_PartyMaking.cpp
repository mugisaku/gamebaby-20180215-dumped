#include"Startup.hpp"
#include"SystemData.hpp"




namespace gmbb{


namespace{


FixedString
label("party making");


class
Message: public Task
{
public:
  Message(): Task(Point(80,100)){}

  void  render(Image&  dst, Point  offset) const noexcept override
  {
    offset += get_base_point();

    dst.print("まものが　あらわれた",offset,system_data::glset);
  }

} message;


coreturn_t
ret_hunger;


void
step(Controller const&  ctrl) noexcept
{
    if(!tmp::next_time)
    {
      constexpr int  interval = 7000;

      tmp::next_time = ctrl.get_time()+interval;
    }

  else
    if(ctrl.get_time() >= tmp::next_time);
    {
      pop_routine(label.pointer);
    }
}


void
return_from_character_making(int  retval) noexcept
{
  terminate_character_making();

  system_data::root_task.push(message);

  tmp::next_time = 0;

  push_routine(label.pointer,step,ret_hunger);
}


}


void
terminate_party_making() noexcept
{
  system_data::root_task.erase(message);
}


void
start_party_making(coreturn_t  ret) noexcept
{
  ret_hunger = ret;

  start_character_making(return_from_character_making,0);
}


}




