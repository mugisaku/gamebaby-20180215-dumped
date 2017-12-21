#ifndef enum_definition_HPP
#define enum_definition_HPP


#include<cstddef>
#include<cstdint>
#include<cstdio>
#include<string>
#include<string_view>
#include<vector>
#include"declaration.hpp"



namespace ty{
namespace ty_types{


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


struct
enum_definition
{
  std::vector<enumerator>  enumerator_list;

  size_t  get_size() const noexcept{return 4;}

  void  print(FILE*  f) const noexcept{}

};


class
enum_declaration: public declaration<enum_definition>
{
};


}


using ty_types::enumerator;
using ty_types::enum_definition;
using ty_types::enum_declaration;



}


#endif




