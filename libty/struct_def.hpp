#ifndef struct_def_HPP
#define struct_def_HPP


#include<cstddef>
#include<cstdint>
#include<cstdio>
#include<string>
#include<string_view>
#include"var_decl.hpp"



namespace ty{
namespace ty_types{


class type_info;


class
struct_member: public var_decl
{
  size_t  m_offset;

public:
  struct_member(const type_decl&  type_decl, std::string_view  name, size_t  offset) noexcept:
  var_decl(type_decl,name),
  m_offset(offset){}

  size_t  get_offset() const noexcept{return m_offset;};

  bool  test_align(size_t  offset_base) const noexcept
  {
    return get_type_decl().get_info().test_align(offset_base+m_offset);
  }

  void  print(FILE*  f=stdout, size_t  offset_base=0) const noexcept
  {
    var_decl::print(f);

    fprintf(f,"(offset %zu) align is %s",offset_base+m_offset,test_align(offset_base)? "right":"wrong");
  }

};


struct
struct_def
{
  std::vector<struct_member>  m_member_list;

  size_t  m_size =0;
  size_t  m_align=0;

public:
  struct_def() noexcept{}

  void  append(const type_decl&  td, std::string  name) noexcept;

  size_t   get_size() const noexcept{return m_size;}
  size_t  get_align() const noexcept{return m_align;}

  bool  test_align(size_t  offset_base) const noexcept;

  void  print(FILE*  f=stdout) const noexcept;

};


}


using ty_types::struct_def;


}


#endif




