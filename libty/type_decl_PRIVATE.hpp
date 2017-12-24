#ifndef type_decl_PRIVATE_HPP
#define type_decl_PRIVATE_HPP


#include"type_decl.hpp"
#include"print.hpp"



namespace ty{
namespace ty_types{


struct
type_decl::
data
{
  size_t  m_reference_count=1;

  type_info  m_type_info;

  std::string  m_name;

};




}}


#endif




