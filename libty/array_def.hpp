#ifndef array_def_HPP
#define array_def_HPP


#include"type_info.hpp"



namespace ty{
namespace ty_types{


class type_info;


struct
array_def
{
  type_info  m_element_type_info;

  size_t  m_number_of_elements;

public:
  array_def() noexcept{}
  array_def(const type_info&  ti, size_t  n) noexcept{set(ti,n);}

  void  set(const type_info&  ti, size_t  n) noexcept;

  const type_info&  get_element_type_info() const noexcept{return m_element_type_info;}

  size_t  get_number_of_elements() const noexcept{return m_number_of_elements;}

  size_t   get_size() const noexcept{return m_element_type_info.get_size()*m_number_of_elements;}
  size_t  get_align() const noexcept{return m_element_type_info.get_align();}

  void  print(FILE*  f=stdout) const noexcept;

};


}


using ty_types::array_def;


}


#endif




