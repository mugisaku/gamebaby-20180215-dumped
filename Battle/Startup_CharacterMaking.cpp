#include"Startup.hpp"
#include"SystemData.hpp"




namespace gmbb{


namespace{


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


void
return_from_name_making(int  retval) noexcept
{
  terminate_name_making();
}


void
return_from_class_choosing(int  retval) noexcept
{
  terminate_class_choosing();

  coprocesses::push(return_from_name_making,coprocess_of_name_making);
}


void
initialize() noexcept
{
  coprocesses::push(return_from_class_choosing,coprocess_of_class_choosing);
}


}


void
terminate_character_making() noexcept
{
//  system_data::root_task.erase(message);
}


const coprocess
coprocess_of_character_making("character_making",initialize,nullptr);


}




