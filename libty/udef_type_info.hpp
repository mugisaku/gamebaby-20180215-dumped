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
udef_type_kind
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
  udef_type_kind  m_kind=udef_type_kind::null;

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


  bool  is_struct() const noexcept{return m_kind == udef_type_kind::struct_;}
  bool    is_enum() const noexcept{return m_kind == udef_type_kind::enum_;}
  bool   is_union() const noexcept{return m_kind == udef_type_kind::union_;}
  bool   is_array() const noexcept{return m_kind == udef_type_kind::array;}

  const struct_def&  get_struct_def() const noexcept{return m_set.st;}
  const   enum_def&    get_enum_def() const noexcept{return m_set.en;}
  const  union_def&   get_union_def() const noexcept{return m_set.un;}
  const  array_def&   get_array_def() const noexcept{return m_set.arr;}

  void  clear() noexcept;

  const std::string&  get_id() const noexcept;

  size_t   get_size() const noexcept;
  size_t  get_align() const noexcept;

  udef_type_kind  get_kind() const noexcept{return m_kind;}

  bool  test_align(size_t  offset_base) const noexcept;

  void  print(FILE*  f=stdout) const noexcept;

};


}


using ty_types::udef_type_info;
using ty_types::udef_type_kind;


}


#endif




