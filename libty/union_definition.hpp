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
  std::vector<variable_declaration>  declaration_list;

  size_t  m_size;
  size_t  m_align;

public:
  size_t  get_size() const noexcept{return m_size;}
  size_t  get_align() const noexcept{return m_align;}

  void  print(FILE*  f) const noexcept{}

};


class
union_declaration: public declaration<union_definition>
{
};


}


using ty_types::union_definition;
using ty_types::union_declaration;


}


#endif




