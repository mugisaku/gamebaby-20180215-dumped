#ifndef union_definition_HPP
#define union_definition_HPP


#include<string>
#include<string_view>
#include<cstdint>
#include<vector>
#include<memory>
#include"variable_declaration.hpp"
#include"declaration.hpp"



namespace ty{
namespace ty_types{


class type_info;


struct
union_definition
{
  std::vector<variable_declaration>  m_declaration_list;

  size_t  m_size =0;
  size_t  m_align=0;

public:
  union_definition() noexcept{}

  void  append(const type_info&  ti, std::string  name) noexcept;

  void  finalize() noexcept;

  size_t   get_size() const noexcept{return m_size;}
  size_t  get_align() const noexcept{return m_align;}

  void  print(FILE*  f) const noexcept;

};


class
union_declaration: public declaration<union_definition>
{
  using declaration::declaration;
};


}


using ty_types::union_definition;
using ty_types::union_declaration;


}


#endif




