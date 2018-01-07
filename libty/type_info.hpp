#ifndef type_info_HPP
#define type_info_HPP


#include<cstddef>
#include<cstdint>
#include<cstdio>
#include"libgbstd/string.hpp"
#include"print.hpp"



namespace ty{
namespace ty_types{


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
  enum class type_kind;

  struct data;

  data*  m_data=nullptr;

  void  unrefer() noexcept;

  type_info(gbstd::string_view  id, type_kind  kind, size_t  size) noexcept;
  type_info(gbstd::string_view  id, type_kind  kind, const type_info&  source) noexcept;
  type_info(data*  new_data) noexcept: m_data(new_data){}
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

  bool  operator==(const type_info&  rhs) const noexcept;
  bool  operator!=(const type_info&  rhs) const noexcept;

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


  const gbstd::string&  get_id() const noexcept;

  size_t   get_size() const noexcept;
  size_t  get_align() const noexcept;

  bool              is_const() const noexcept;
  bool           is_volatile() const noexcept;
  bool     is_const_volatile() const noexcept;
  bool           is_integral() const noexcept;
  bool  is_unsigned_integral() const noexcept;
  bool            is_boolean() const noexcept;
  bool               is_void() const noexcept;
  bool            is_pointer() const noexcept;
  bool       is_null_pointer() const noexcept;
  bool    is_generic_pointer() const noexcept;
  bool   is_function_pointer() const noexcept;
  bool          is_reference() const noexcept;
  bool   is_rvalue_reference() const noexcept;
  bool             is_struct() const noexcept;
  bool               is_enum() const noexcept;
  bool              is_union() const noexcept;
  bool              is_array() const noexcept;


  const  type_info&  get_source_type_info() const noexcept;
  const  array_def&   get_array_def() const noexcept;

  struct_def&  get_struct_def() const noexcept;
    enum_def&    get_enum_def() const noexcept;
   union_def&   get_union_def() const noexcept;



  static type_info  make_i8()  noexcept;
  static type_info  make_u8()  noexcept;
  static type_info  make_i16() noexcept;
  static type_info  make_u16() noexcept;
  static type_info  make_i32() noexcept;
  static type_info  make_u32() noexcept;

  static type_info  make_boolean()         noexcept;
  static type_info  make_void()            noexcept;
  static type_info  make_null_pointer()    noexcept;
  static type_info  make_generic_pointer() noexcept;
  static type_info  make_function_pointer() noexcept;

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


}


#endif




