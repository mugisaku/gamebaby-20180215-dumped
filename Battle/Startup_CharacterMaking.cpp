#include"Startup.hpp"
#include"SystemData.hpp"




namespace gmbb{


namespace{


FixedString
label("character making");


class
Message: public Task
{
public:
  Message(): Task(Point(64,16)){}

  void  render(Image&  dst, Point  offset) const noexcept override
  {
    offset += get_base_point();

    dst.print("しゅじんこうの　クラスを　きめてください",offset,sys::glset);
  }

} message;


coreturn_t
ret_hunger;


void
return_from_name_making(int  retval) noexcept
{
  terminate_name_making();

    if(ret_hunger)
    {
      ret_hunger(retval);
    }
}


void
return_from_class_choosing(int  retval) noexcept
{
  terminate_class_choosing();

  start_name_making(return_from_name_making);
}


}


void
terminate_character_making() noexcept
{
//  system_data::root_task.erase(message);
}


void
start_character_making(coreturn_t  ret, int  number) noexcept
{
  ret_hunger = ret;

  start_class_choosing(return_from_class_choosing);
}


}




