#ifndef enum_def_HPP
#define enum_def_HPP


#include<cstddef>
#include<cstdint>
#include<cstdio>
#include"libgbstd/string.hpp"
#include<vector>
#include"print.hpp"



namespace ty{
namespace ty_types{


class
enumerator
{
  gbstd::string  m_name;

  int  m_value;

public:
  enumerator(gbstd::string_view  name, int  value) noexcept:
  m_name(name),
  m_value(value){}

  const gbstd::string&  get_name() const noexcept{return m_name;}

  int  get_value() const noexcept{return m_value;}

  void  print(FILE*  f) const noexcept{fprintf(f,"%s = %d",m_name.data(),m_value);}

};


class
enum_def
{
  std::vector<enumerator>  m_enumerator_list;

  int  m_last_value=0;

public:
  enum_def() noexcept{}

  void  append(gbstd::string_view  name            ) noexcept;
  void  append(gbstd::string_view  name, int  value) noexcept;

  size_t   get_size() const noexcept{return 4;}
  size_t  get_align() const noexcept{return 4;}

  void  print(FILE*  f=stdout) const noexcept;

};


}


using ty_types::enumerator;
using ty_types::enum_def;



}


#endif




