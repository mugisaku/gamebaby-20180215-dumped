#ifndef union_type_info_HPP
#define union_type_info_HPP


#include<string>
#include<string_view>
#include<cstdint>
#include<vector>
#include"declaration.hpp"



namespace ts{
namespace types{


class type_info;


class
union_type_info
{
  uint32_t  m_index;

  std::vector<declaration>  declaration_list;

  size_t  m_size;
  size_t  m_align;

public:

};


}


using types::union_type_info;


}


#endif




