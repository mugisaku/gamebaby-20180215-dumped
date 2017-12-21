#ifndef struct_definition_HPP
#define struct_definition_HPP


#include<cstddef>
#include<cstdint>
#include<cstdio>
#include<string>
#include<string_view>
#include<memory>
#include"variable_declaration.hpp"
#include"declaration.hpp"



namespace ty{
namespace ty_types{


class type_info;


class
struct_member: public variable_declaration
{
  size_t  m_offset;

public:
  struct_member(const type_info&  type_info, std::string_view  name, size_t  offset) noexcept:
  variable_declaration(type_info,name),
  m_offset(offset){}

  size_t  get_offset() const noexcept{return m_offset;};

  void  print(FILE*  f) const noexcept
  {
    variable_declaration::print(f);

    fprintf(f,"(offset %zu)",m_offset);
  }

};


struct
struct_definition
{
  std::vector<struct_member>  m_member_list;

  size_t  m_size =0;
  size_t  m_align=0;

public:
  struct_definition() noexcept{}

  void  append(const type_info&  ti, std::string  name) noexcept;

  void  finalize() noexcept;

  size_t   get_size() const noexcept{return m_size;}
  size_t  get_align() const noexcept{return m_align;}

  void  print(FILE*  f) const noexcept;

};


class
struct_declaration: public declaration<struct_definition>
{
  using declaration::declaration;
};


}


using ty_types::struct_definition;
using ty_types::struct_declaration;


}


#endif



