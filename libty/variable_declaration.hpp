#ifndef variable_declaration_HPP
#define variable_declaration_HPP


#include"type_info.hpp"
#include<vector>



namespace ty{
namespace ty_types{


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
    fprintf(f,"%s  ",m_name.data());

    m_type_info.print(f);
  }

};




}


using ty_types::variable_declaration;


}


#endif




