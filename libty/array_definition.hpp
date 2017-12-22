#ifndef array_definition_HPP
#define array_definition_HPP


#include<cstddef>
#include<cstdint>
#include<cstdio>
#include<string>
#include<string_view>
#include"variable_declaration.hpp"



namespace ty{
namespace ty_types{


class type_info;


struct
array_definition
{
  type_info  m_element_type_info;

  size_t  m_number_of_elements;

public:
  array_definition() noexcept{}
  array_definition(const type_info&  ti, size_t  n) noexcept{set(ti,n);}

  void  set(const type_info&  ti, size_t  n) noexcept;

  const type_info&  get_element_type_info() const noexcept{return m_element_type_info;}

  size_t  get_number_of_elements() const noexcept{return m_number_of_elements;}

  size_t   get_size() const noexcept{return m_element_type_info.get_size()*m_number_of_elements;}
  size_t  get_align() const noexcept{return m_element_type_info.get_align();}

  void  print(FILE*  f, size_t  offset_base) const noexcept;

};


}


using ty_types::array_definition;


}


#endif




