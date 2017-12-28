#ifndef space_HPP
#define space_HPP


#include"libty/ty.hpp"
#include"libtok/stream_reader.hpp"
#include<list>



namespace ipre{
namespace ipre_types{


class
space
{
  space*  m_parent=nullptr;

  std::list<ty::type_decl>  m_type_decl_list;
  std::list<ty::var_decl>    m_var_decl_list;

public:
  const space*  get_parent(              ) const noexcept{return m_parent         ;}
  void          set_parent(space*  parent)       noexcept{       m_parent = parent;}

  const ty::type_decl*  find_type_decl(std::string_view  name) const noexcept;
  const ty::var_decl*   find_var_decl(std::string_view  name) const noexcept;

};


}


using ipre_types::space;



}


#endif




