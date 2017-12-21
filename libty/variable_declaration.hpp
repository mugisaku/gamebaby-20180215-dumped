#ifndef variable_declaration_HPP
#define variable_declaration_HPP


#include"type_info.hpp"
#include<vector>



namespace ty{
namespace ty_types{


constexpr
size_t
get_aligned_offset(size_t  offset, size_t  align) noexcept
{
    if(align)
    {
      offset = (offset+(align-1))/align*align;
    }


  return offset;
}


class
variable_declaration
{
  type_info  m_type_info;

  std::string  m_name;

public:
  variable_declaration(const type_info&  type_info, std::string_view  name) noexcept:
  m_type_info(type_info),
  m_name(name){}

  const type_info&  get_type_info() const noexcept{return m_type_info;}

  const std::string&  get_name() const noexcept{return m_name;}

  void  print(FILE*  f) const noexcept
  {
    m_type_info.print_human_readable(f);

    fprintf(f,"  %s",m_name.data());
  }

};




}


using ty_types::variable_declaration;


}


#endif




