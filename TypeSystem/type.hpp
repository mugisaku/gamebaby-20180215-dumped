#ifndef type_HPP
#define type_HPP


#include"simple_type.hpp"
#include"cv_qualified_type.hpp"
#include"type_info.hpp"



namespace ts{
namespace types{


enum class
type_kind
{
  simple,
  cv_qualified,
  alias,
  pointer,
  reference,

};




class
type
{
  type_kind  m_kind;

  union type_data{
    types::simple_type        simple_type;
    types::cv_qualified_type     cvq_type;

    type_data(){}
   ~type_data(){}

  } m_data;

public:
  type(simple_type  s) noexcept: m_kind(type_kind::simple){m_data.simple_type = s;}

  bool  is_simple() const noexcept{return m_kind == type_kind::simple;}
  bool  is_cv_qualified() const noexcept{return m_kind == type_kind::cv_qualified;}
  bool  is_alias() const noexcept{return m_kind == type_kind::alias;}
  bool  is_pointer() const noexcept{return m_kind == type_kind::pointer;}
  bool  is_reference() const noexcept{return m_kind == type_kind::reference;}

  size_t   get_size() const noexcept;
  size_t  get_align() const noexcept;

  void  print_id(char*  buf, size_t  bufsz) const noexcept;

};




}


using types::type;


}


#endif




