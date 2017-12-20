#ifndef declaration_HPP
#define declaration_HPP


#include"type_info.hpp"



namespace ty{
namespace declarations{


class
declaration
{
  type_info  m_type_info;

  std::string  m_name;

public:
  declaration(const type_info&  type_info, std::string_view  name) noexcept:
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


using declarations::declaration;


}


#endif




