#include"environment.hpp"
#include<unordered_map>






namespace gbstd{
namespace environment{


unsigned int
count_of_report;


namespace{


std::unordered_map<std::string,std::string>
variables;


}


uint8_t
fn_keystate;


void
set_value(std::string_view  name, std::string_view  value) noexcept
{
  variables[name] = value;
}


const std::string&
get_value(std::string_view  name) noexcept
{
  return variables[name];
}


}}




