#ifndef enum_definition_HPP
#define enum_definition_HPP


#include<cstddef>
#include<cstdint>
#include<cstdio>
#include<string>
#include<string_view>
#include<vector>



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

  void  print(FILE*  f) const noexcept{fprintf(f,"%s = %d",m_name.data(),m_value);}

};


class
enum_definition
{
  std::vector<enumerator>  m_enumerator_list;

  int  m_last_value=0;

public:
  enum_definition() noexcept{}

  void  append(std::string_view  name            ) noexcept;
  void  append(std::string_view  name, int  value) noexcept;

  size_t   get_size() const noexcept{return 4;}
  size_t  get_align() const noexcept{return 4;}

  void  print(FILE*  f) const noexcept;

};


}


using ty_types::enumerator;
using ty_types::enum_definition;



}


#endif




