#include"gmbb_environment.hpp"
#include<unordered_map>






namespace gmbb{
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
set_value(char const*  name, char const*  value) noexcept
{
  variables[name] = value;
}


std::string const&
get_value(char const*  name) noexcept
{
  return variables[name];
}


}}




