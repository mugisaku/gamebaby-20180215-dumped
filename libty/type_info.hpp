#ifndef type_info_HPP
#define type_info_HPP


#include<cstddef>
#include<cstdint>
#include<cstdio>
#include<string>
#include<string_view>
#include"print.hpp"



namespace ty{
namespace ty_types{


enum class
type_kind
{
  null,
  integral,
  unsigned_integral,
  boolean,
  void_,
  const_qualified,
  volatile_qualified,
  const_volatile_qualified,
  null_pointer,
  generic_pointer,
  pointer,
  reference,
  rvalue_reference,
  function_pointer,

  enum_,
  array,
  union_,
  struct_,

};


class type_info;
class  array_def;
class   enum_def;
class  union_def;
class struct_def;


constexpr size_t  pointer_type_size = 4;
constexpr size_t     word_type_size = 4;


class
type_info
{
  struct data;

  data*  m_data=nullptr;

  void  unrefer() noexcept;

  type_info(type_kind  kind, std::string_view  id, size_t  size) noexcept;
  type_info(type_kind  kind, std::string_view  id, const type_info&  source) noexcept;
  type_info(array_def&&  def) noexcept;
  type_info(enum_def&&  def) noexcept;
  type_info(union_def&&  def) noexcept;
  type_info(struct_def&&  def) noexcept;

public:
  type_info(                      ) noexcept{}
  type_info(const type_info&   rhs) noexcept{*this = rhs;}
  type_info(      type_info&&  rhs) noexcept{*this = std::move(rhs);}
 ~type_info(){unrefer();}

  type_info&  operator=(const type_info&   rhs) noexcept;
  type_info&  operator=(      type_info&&  rhs) noexcept;

  bool  operator==(const type_info&  rhs) const noexcept{return get_id() == rhs.get_id();}
  bool  operator!=(const type_info&  rhs) const noexcept{return get_id() != rhs.get_id();}

  operator bool() const noexcept{return m_data;}

  type_info             add_const() const noexcept;
  type_info          add_volatile() const noexcept;
  type_info    add_const_volatile() const noexcept;
  type_info           add_pointer() const noexcept;
  type_info         add_reference() const noexcept;
  type_info  add_rvalue_reference() const noexcept;

  type_info             remove_const() const noexcept;
  type_info          remove_volatile() const noexcept;
  type_info    remove_const_volatile() const noexcept;
  type_info           remove_pointer() const noexcept;
  type_info         remove_reference() const noexcept;
  type_info  remove_rvalue_reference() const noexcept;


  const std::string&  get_id() const noexcept;

  size_t   get_size() const noexcept;
  size_t  get_align() const noexcept;

  type_kind  get_kind() const noexcept;


  bool              is_const() const noexcept{return get_kind() == type_kind::const_qualified;}
  bool           is_volatile() const noexcept{return get_kind() == type_kind::volatile_qualified;}
  bool     is_const_volatile() const noexcept{return get_kind() == type_kind::const_volatile_qualified;}
  bool           is_integral() const noexcept{return get_kind() == type_kind::integral;}
  bool  is_unsigned_integral() const noexcept{return get_kind() == type_kind::unsigned_integral;}
  bool            is_boolean() const noexcept{return get_kind() == type_kind::boolean;}
  bool               is_void() const noexcept{return get_kind() == type_kind::void_;}
  bool            is_pointer() const noexcept{return get_kind() == type_kind::pointer;}
  bool       is_null_pointer() const noexcept{return get_kind() == type_kind::null_pointer;}
  bool    is_generic_pointer() const noexcept{return get_kind() == type_kind::generic_pointer;}
  bool   is_function_pointer() const noexcept{return get_kind() == type_kind::function_pointer;}
  bool          is_reference() const noexcept{return get_kind() == type_kind::reference;}
  bool   is_rvalue_reference() const noexcept{return get_kind() == type_kind::rvalue_reference;}
  bool             is_struct() const noexcept{return get_kind() == type_kind::struct_;}
  bool               is_enum() const noexcept{return get_kind() == type_kind::enum_;}
  bool              is_union() const noexcept{return get_kind() == type_kind::union_;}
  bool              is_array() const noexcept{return get_kind() == type_kind::array;}


  const  type_info&  get_source_type_info() const noexcept;
  const  array_def&   get_array_def() const noexcept;

  struct_def&  get_struct_def() const noexcept;
    enum_def&    get_enum_def() const noexcept;
   union_def&   get_union_def() const noexcept;



  static type_info  make_i8()  noexcept{return type_info(type_kind::integral         , "i8",1);}
  static type_info  make_u8()  noexcept{return type_info(type_kind::unsigned_integral, "u8",1);}
  static type_info  make_i16() noexcept{return type_info(type_kind::integral         ,"i16",2);}
  static type_info  make_u16() noexcept{return type_info(type_kind::unsigned_integral,"u16",2);}
  static type_info  make_i32() noexcept{return type_info(type_kind::integral         ,"i32",4);}
  static type_info  make_u32() noexcept{return type_info(type_kind::unsigned_integral,"u32",4);}

  static type_info  make_boolean()         noexcept{return type_info(type_kind::boolean,"b",1);}
  static type_info  make_void()            noexcept{return type_info(type_kind::void_,"v",0);}
  static type_info  make_null_pointer()    noexcept{return type_info(type_kind::null_pointer,"np",pointer_type_size);}
  static type_info  make_generic_pointer() noexcept{return type_info(type_kind::generic_pointer,"gp",pointer_type_size);}

  static type_info  make_array(const type_info&  ti, size_t  n) noexcept;
  static type_info  make_empty_enum()   noexcept;
  static type_info  make_empty_struct() noexcept;
  static type_info  make_empty_union()  noexcept;

  bool  test_align(size_t  offset_base=0) const noexcept;

  void  print_id(FILE*  f=stdout) const noexcept;

  void  print_size_and_align(FILE*  f=stdout) const noexcept;

  void  print(FILE*  f=stdout) const noexcept;

};


}


using ty_types::type_info;
using ty_types::type_kind;


}


#endif




