#ifndef enum_type_info_HPP
#define enum_type_info_HPP


#include<cstddef>
#include<cstdint>
#include<cstdio>
#include<string>
#include<string_view>



namespace ts{
namespace types{


class
enumerator
{
  std::string  m_name;

  int  m_value;

public:
  enumerator(std::string_view  name, int  value) noexcept:
  m_name(name),
  m_value(value){}

  const std::string&  get_name() const noexcept{return m_name;}

  int  get_value() const noexcept{return m_value;}

};


using enum_definition = std::vector<enumerator>;


}


using types::enumerator;
using types::enum_definition;


}


#endif




