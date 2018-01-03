#include"Startup.hpp"
#include"SystemData.hpp"




namespace{


class
Message: public gbstd::task
{
public:
  Message(): task(gbstd::point(64,16)){}

  void  render(gbstd::image&  dst, gbstd::point  offset) const noexcept override
  {
    offset += get_base_point();

    dst.print("しゅじんこうの　クラスを　きめてください",offset,sys::font);
  }

} message;


void
step(uint32_t&  pc) noexcept
{
    switch(pc)
    {
  case(0):
      gbstd::playworks::push(nullptr,playwork_of_class_choosing);
      ++pc;
      break;
  case(1):
      terminate_class_choosing();

      gbstd::playworks::push(nullptr,playwork_of_name_making);
      ++pc;
      break;
  case(2):
      terminate_name_making();
      ++pc;
  default:
      gbstd::playworks::pop();
    }
}


}


void
terminate_character_making() noexcept
{
//  system_data::root_task.erase(message);
}


const gbstd::playwork
playwork_of_character_making("character_making",step);




