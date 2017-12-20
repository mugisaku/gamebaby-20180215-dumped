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


class
enum_type_info
{
  uint32_t  m_index;

  std::vector<enumerator>  m_table;

public:
  enum_type_info(uint32_t  i, std::vector<enumerator>&&  table) noexcept:
  m_index(i),
  m_table(std::move(table)){}

  uint32_t  get_index() const noexcept{return m_index;}

  const std::vector<enumerators>&  get_table() const noexcept{return m_table;}

};


}


using types::enumerator;
using types::enum_type_info;


}


#endif




