#ifndef struct_type_info_HPP
#define struct_type_info_HPP


#include<cstddef>
#include<cstdint>
#include<cstdio>
#include<string>
#include<string_view>
#include"declaration.hpp"



namespace ts{
namespace types{


class type_info;


class
struct_type_info
{
  uint32_t  m_index;

  std::vector<declaration>  declaration_list;

  size_t  m_size;
  size_t  m_align;

public:

};


}


using types::struct_type_info;


}


#endif




