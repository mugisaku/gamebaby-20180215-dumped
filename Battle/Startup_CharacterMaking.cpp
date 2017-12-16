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
step(uint32_t  count) noexcept
{
    switch(count)
    {
  case(0):
      coprocesses::push(nullptr,coprocess_of_class_choosing);
      break;
  case(1):
      terminate_class_choosing();

      coprocesses::push(nullptr,coprocess_of_name_making);
      break;
  case(2):
      terminate_name_making();
  default:
      coprocesses::pop();
    }
}


}


void
terminate_character_making() noexcept
{
//  system_data::root_task.erase(message);
}


const coprocess
coprocess_of_character_making("character_making",step);


}




