#ifndef user_defined_type_declaration_HPP
#define user_defined_type_declaration_HPP


#include"type_info.hpp"
#include"array_definition.hpp"
#include"enum_definition.hpp"
#include"struct_definition.hpp"
#include"union_definition.hpp"



namespace ty{
namespace ty_types{


enum class
user_defined_type_kind
{
  null,
  function,
  array,
  enum_,
  struct_,
  union_,

};


class
user_defined_type_declaration
{
  user_defined_type_kind  m_kind=user_defined_type_kind::null;

  union set_t{
     array_definition  arr;
      enum_definition   en;
    struct_definition   st;
     union_definition   un;

    set_t(){}
   ~set_t(){}

  } m_set;


public:
  user_defined_type_declaration() noexcept{}
  user_defined_type_declaration(array_definition&&  arr) noexcept;
  user_defined_type_declaration(struct_definition&&  st) noexcept;
  user_defined_type_declaration(enum_definition&&  en) noexcept;
  user_defined_type_declaration(union_definition&&  un) noexcept;
  user_defined_type_declaration(const user_defined_type_declaration&   rhs) noexcept{*this = rhs;}
  user_defined_type_declaration(      user_defined_type_declaration&&  rhs) noexcept{*this = std::move(rhs);}
 ~user_defined_type_declaration(){clear();}

  user_defined_type_declaration&  operator=(const user_defined_type_declaration&   rhs) noexcept;
  user_defined_type_declaration&  operator=(      user_defined_type_declaration&&  rhs) noexcept;

  bool  operator==(const user_defined_type_declaration&  rhs) const noexcept{return get_id() == rhs.get_id();}
  bool  operator!=(const user_defined_type_declaration&  rhs) const noexcept{return get_id() != rhs.get_id();}


  void  clear() noexcept;

  const std::string&  get_id() const noexcept;

  size_t   get_size() const noexcept;
  size_t  get_align() const noexcept;

  user_defined_type_kind  get_kind() const noexcept{return m_kind;}

  void  print(FILE*  f=stdout, size_t  offset_base=0) const noexcept;

};


}


using ty_types::user_defined_type_declaration;
using ty_types::user_defined_type_kind;


}


#endif




