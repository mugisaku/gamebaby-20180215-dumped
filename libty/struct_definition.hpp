#ifndef struct_definition_HPP
#define struct_definition_HPP


#include<cstddef>
#include<cstdint>
#include<cstdio>
#include<string>
#include<string_view>
#include"declaration.hpp"



namespace ty{
namespace definitions{


class type_info;


class
struct_definition
{
  std::vector<declaration>  declaration_list;

  size_t  m_size;
  size_t  m_align;

public:

};


}


using definitions::struct_definition;


}


#endif




