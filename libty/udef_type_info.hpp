#ifndef udef_type_info_HPP
#define udef_type_info_HPP


#include"type_info.hpp"
#include"array_def.hpp"
#include"enum_def.hpp"
#include"struct_def.hpp"
#include"union_def.hpp"



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
udef_type_info
{
  user_defined_type_kind  m_kind=user_defined_type_kind::null;

  union set_t{
     array_def  arr;
      enum_def   en;
    struct_def   st;
     union_def   un;

    set_t(){}
   ~set_t(){}

  } m_set;


public:
  udef_type_info() noexcept{}
  udef_type_info(array_def&&  arr) noexcept;
  udef_type_info(struct_def&&  st) noexcept;
  udef_type_info(enum_def&&  en) noexcept;
  udef_type_info(union_def&&  un) noexcept;
  udef_type_info(const udef_type_info&   rhs) noexcept{*this = rhs;}
  udef_type_info(      udef_type_info&&  rhs) noexcept{*this = std::move(rhs);}
 ~udef_type_info(){clear();}

  udef_type_info&  operator=(const udef_type_info&   rhs) noexcept;
  udef_type_info&  operator=(      udef_type_info&&  rhs) noexcept;

  bool  operator==(const udef_type_info&  rhs) const noexcept{return get_id() == rhs.get_id();}
  bool  operator!=(const udef_type_info&  rhs) const noexcept{return get_id() != rhs.get_id();}


  void  clear() noexcept;

  const std::string&  get_id() const noexcept;

  size_t   get_size() const noexcept;
  size_t  get_align() const noexcept;

  user_defined_type_kind  get_kind() const noexcept{return m_kind;}

  void  print(FILE*  f=stdout, size_t  offset_base=0) const noexcept;

};


}


using ty_types::udef_type_info;
using ty_types::user_defined_type_kind;


}


#endif




