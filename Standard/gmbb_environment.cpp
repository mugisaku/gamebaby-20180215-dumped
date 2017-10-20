#include"gmbb_environment.hpp"
#include<unordered_map>






namespace gmbb{
namespace env{


unsigned int
count_of_report;


namespace{


std::unordered_map<std::u16string,std::u16string>
variables;


}


uint8_t  fn_keystate;


void
set_value(const char16_t*  name, const char16_t*  value) noexcept
{
  variables[name] = value;
}


const std::u16string&
get_value(const char16_t*  name) noexcept
{
  return variables[name];
}


}}




