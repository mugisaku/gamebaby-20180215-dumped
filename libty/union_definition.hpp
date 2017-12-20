#ifndef union_definition_HPP
#define union_definition_HPP


#include<string>
#include<string_view>
#include<cstdint>
#include<vector>
#include"declaration.hpp"



namespace ty{
namespace definitions{


class type_info;


class
union_definition
{
  std::vector<declaration>  declaration_list;

  size_t  m_size;
  size_t  m_align;

public:

};


}


using definitions::union_definition;


}


#endif




