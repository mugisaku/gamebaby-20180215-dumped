#ifndef var_decl_HPP
#define var_decl_HPP


#include"type_decl.hpp"
#include<vector>



namespace ty{
namespace ty_types{


class
var_decl
{
  type_decl  m_type_decl;

  std::string  m_name;

public:
  var_decl(const type_decl&  type_decl, std::string_view  name) noexcept:
  m_type_decl(type_decl),
  m_name(name){}

  const type_decl&  get_type_decl() const noexcept{return m_type_decl;}

  const std::string&  get_name() const noexcept{return m_name;}

  void  print(FILE*  f) const noexcept
  {
    m_type_decl.print(f);

    m_type_decl.get_info().print_size_and_align(f);

    fprintf(f,"  %s",m_name.data());
  }

};




}


using ty_types::var_decl;


}


#endif




