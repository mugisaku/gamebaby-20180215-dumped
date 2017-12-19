#ifndef type_info_HPP
#define type_info_HPP


#include<cstddef>
#include<cstdint>
#include<cstdio>
#include<string>
#include<string_view>
#include"pointer_type_info.hpp"



namespace ts{
namespace types{


enum class
type_qualifier
{
  none           = 0,
  const_         = 1,
  volatile_      = 2,
  const_volatile = 3,

};


enum class
type_kind
{
  null,
  signed_integral,
  unsigned_integral,
  boolean,
  void_,
  pointer,
  reference,
  array,

};


class type_info;


class
signed_integral_type_info
{
  size_t  m_size;

public:
  constexpr signed_integral_type_info(size_t  size) noexcept:
  m_size(size){}

  constexpr size_t   get_size() const noexcept{return m_size;}

};


class
unsigned_integral_type_info
{
  size_t  m_size;

public:
  constexpr unsigned_integral_type_info(size_t  size) noexcept:
  m_size(size){}

  constexpr size_t   get_size() const noexcept{return m_size;}

};


class
boolean_type_info
{
  size_t  m_size;

public:
  constexpr boolean_type_info(size_t  size) noexcept:
  m_size(size){}

  constexpr size_t   get_size() const noexcept{return m_size;}

};


class
void_type_info
{
public:
  constexpr void_type_info() noexcept{}

};


class
reference_type_info
{
  const type_info*  m_target;

public:
  constexpr reference_type_info(const type_info&  target) noexcept:
  m_target(&target){}

  constexpr const type_info&   get_target() const noexcept{return *m_target;}

};


class
array_type_info
{
  const type_info*  m_target;

  size_t  m_number_of_elements;

public:
  constexpr array_type_info(const type_info&  target, size_t  number_of_elements) noexcept:
  m_target(&target),
  m_number_of_elements(number_of_elements){}

  constexpr const type_info&   get_target() const noexcept{return *m_target;}

  constexpr size_t  get_number_of_elements() const noexcept{return m_number_of_elements;}

  inline size_t  get_size() const noexcept;

};


struct
variation_set
{
  const type_info*           const_removed_version;
  const type_info*        volatile_removed_version;
  const type_info*  const_volatile_removed_version;
  const type_info*         pointer_removed_version;
  const type_info*       reference_removed_version;

  variation_set(const type_info*  p) noexcept:
           const_removed_version(p),
        volatile_removed_version(p),
  const_volatile_removed_version(p),
         pointer_removed_version(p),
       reference_removed_version(p){}
  

};


class
type_info
{
  variation_set  m_variation_set;

  std::string  m_id;
  std::string  m_hid;

  type_qualifier  m_qualifier;

  type_kind  m_kind;

  union data{
      signed_integral_type_info  sint_info;
    unsigned_integral_type_info  uint_info;

    boolean_type_info  bool_info;

    void_type_info  void_info;

    pointer_type_info  ptr_info;
    reference_type_info  ref_info;

    array_type_info  arr_info;

    data(){}
   ~data(){}

  } m_data;

public:
  type_info() noexcept:
  m_variation_set(this),
  m_qualifier(type_qualifier::none),
  m_kind(type_kind::null){}

  type_info(std::string_view  id, signed_integral_type_info  sint_info) noexcept:
  m_variation_set(this),
  m_id(id),
  m_qualifier(type_qualifier::none),
  m_kind(type_kind::signed_integral){m_data.sint_info = sint_info;}

  type_info(std::string_view  id, unsigned_integral_type_info  uint_info) noexcept:
  m_variation_set(this),
  m_id(id),
  m_qualifier(type_qualifier::none),
  m_kind(type_kind::unsigned_integral){m_data.uint_info = uint_info;}

  type_info(std::string_view  id, boolean_type_info  bool_info) noexcept:
  m_variation_set(this),
  m_id(id),
  m_qualifier(type_qualifier::none),
  m_kind(type_kind::boolean){m_data.bool_info = bool_info;}

  type_info(std::string_view  id, void_type_info  void_info) noexcept:
  m_variation_set(this),
  m_id(id),
  m_qualifier(type_qualifier::none),
  m_kind(type_kind::void_){m_data.void_info = void_info;}

  type_info(std::string_view  id, pointer_type_info  ptr_info) noexcept:
  m_variation_set(this),
  m_id(id),
  m_qualifier(type_qualifier::none),
  m_kind(type_kind::pointer){m_data.ptr_info = ptr_info;}

  type_info(std::string_view  id, reference_type_info  ref_info) noexcept:
  m_variation_set(this),
  m_id(id),
  m_qualifier(type_qualifier::none),
  m_kind(type_kind::reference){m_data.ref_info = ref_info;}

  type_info(std::string_view  id, array_type_info  arr_info) noexcept:
  m_variation_set(this),
  m_id(id),
  m_qualifier(type_qualifier::none),
  m_kind(type_kind::array){m_data.arr_info = arr_info;}

  const std::string&  get_id() const noexcept{return m_id;}

  type_qualifier  get_qualifier() const noexcept{return m_qualifier;}

  size_t   get_size() const noexcept;
  size_t  get_align() const noexcept;

  type_kind  get_kind() const noexcept{return m_kind;}

  bool  is_const() const noexcept{return static_cast<int>(m_qualifier)&static_cast<int>(type_qualifier::const_);}
  bool  is_volatile() const noexcept{return static_cast<int>(m_qualifier)&static_cast<int>(type_qualifier::const_);}
  bool  is_const_volatile() const noexcept{return m_qualifier == type_qualifier::const_volatile;}

  bool  is_signed_integral() const noexcept{return m_kind == type_kind::signed_integral;}
  bool  is_unsigned_integral() const noexcept{return m_kind == type_kind::unsigned_integral;}
  bool  is_boolean() const noexcept{return m_kind == type_kind::boolean;}
  bool  is_void() const noexcept{return m_kind == type_kind::void_;}
  bool  is_array() const noexcept{return m_kind == type_kind::array;}
  bool  is_pointer() const noexcept{return m_kind == type_kind::pointer;}
  bool  is_reference() const noexcept{return m_kind == type_kind::reference;}

  const   signed_integral_type_info&  get_signed_integral_info() const noexcept{return m_data.sint_info;}
  const unsigned_integral_type_info&  get_unsigned_integral_info() const noexcept{return m_data.uint_info;}
  const           boolean_type_info&  get_boolean_info() const noexcept{return m_data.bool_info;}
  const              void_type_info&  get_void_info() const noexcept{return m_data.void_info;}
  const             array_type_info&  get_array_info() const noexcept{return m_data.arr_info;}
  const           pointer_type_info&  get_pointer_info() const noexcept{return m_data.ptr_info;}
  const         reference_type_info&  get_reference_info() const noexcept{return m_data.ref_info;}

  const type_info&  add_const() const noexcept;
  const type_info&  add_volatile() const noexcept;
  const type_info&  add_const_volatile() const noexcept;
  const type_info&  add_pointer() const noexcept;
  const type_info&  add_reference() const noexcept;

  const type_info&  remove_const() const noexcept{return *m_variation_set.const_removed_version;}
  const type_info&  remove_volatile() const noexcept{return *m_variation_set.volatile_removed_version;}
  const type_info&  remove_const_volatile() const noexcept{return *m_variation_set.const_volatile_removed_version;}
  const type_info&  remove_pointer() const noexcept{return *m_variation_set.pointer_removed_version;}
  const type_info&  remove_reference() const noexcept{return *m_variation_set.reference_removed_version;}

  void  print(FILE*  f=stdout) const noexcept
  {
    fprintf(f,"   id %s\n",m_id.data());
    fprintf(f," size %zu\n",get_size());
    fprintf(f,"align %zu\n",get_align());
  }

};


inline size_t
array_type_info::
get_size() const noexcept
{
  return m_target->get_size()*m_number_of_elements;
}


}


using types::type_info;
using types::signed_integral_type_info;
using types::unsigned_integral_type_info;
using types::boolean_type_info;
using types::void_type_info;
using types::array_type_info;
using types::pointer_type_info;
using types::reference_type_info;
using types::type_kind;
using types::type_qualifier;
using types::variation_set;


}


#endif




