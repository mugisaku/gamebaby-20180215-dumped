#ifndef type_info_PRIVATE_HPP
#define type_info_PRIVATE_HPP


#include"type_info.hpp"
#include"array_def.hpp"
#include"enum_def.hpp"
#include"struct_def.hpp"
#include"union_def.hpp"
#include"signature.hpp"


namespace ty{
namespace ty_types{


enum class
type_info::
type_kind
{
  null,
  integral,
  unsigned_integral,
  boolean,
  void_,
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


constexpr unsigned int           const_flag  = 1;
constexpr unsigned int        volatile_flag  = 2;
constexpr unsigned int  const_volatile_flags = 3;


struct
type_info::
data
{
  size_t  m_reference_count=1;

  std::string  m_id;

  type_kind  m_kind=type_kind::null;

  unsigned int  m_qualification_flags=0;

  union set{
    size_t  size;

    type_info  ti;

     array_def  arr;
      enum_def   en;
    struct_def   st;
     union_def   un;

    signature  sig;

    set(){}
   ~set(){}

  } m_set;


  ~data()
  {
      switch(m_kind)
      {
    case(type_kind::pointer):
    case(type_kind::reference):
        m_set.ti.~type_info();
        break;
    case(type_kind::boolean):
    case(type_kind::null_pointer):
    case(type_kind::generic_pointer):
    case(type_kind::integral):
    case(type_kind::unsigned_integral):
        break;
    case(type_kind::function_pointer): m_set.sig.~signature();break;
    case(type_kind::array           ): m_set.arr.~array_def();break;
    case(type_kind::struct_         ): m_set.st.~struct_def();break;
    case(type_kind::enum_           ): m_set.en.~enum_def();break;
    case(type_kind::union_          ): m_set.un.~union_def();break;
        }
  }


  bool  operator==(const data&  rhs) const noexcept
  {
    return((m_qualification_flags == rhs.m_qualification_flags) &&
           (m_id                  == rhs.m_id                 ));
  }


  data*  clone(unsigned int  new_flags) const noexcept
  {
    auto  new_data = new data;

    new_data->m_id                  = m_id;
    new_data->m_kind                = m_kind;
    new_data->m_qualification_flags = new_flags;

      switch(m_kind)
      {
    case(type_kind::pointer):
    case(type_kind::reference):
        new(&new_data->m_set.ti) type_info(m_set.ti);
        break;
    case(type_kind::boolean):
    case(type_kind::null_pointer):
    case(type_kind::generic_pointer):
    case(type_kind::integral):
    case(type_kind::unsigned_integral):
        new_data->m_set.size = m_set.size;
        break;
    case(type_kind::function_pointer): new(&new_data->m_set)  signature(m_set.sig);break;
    case(type_kind::array           ): new(&new_data->m_set)  array_def(m_set.arr);break;
    case(type_kind::struct_         ): new(&new_data->m_set) struct_def(m_set.st);break;
    case(type_kind::enum_           ): new(&new_data->m_set)   enum_def(m_set.en);break;
    case(type_kind::union_          ): new(&new_data->m_set)  union_def(m_set.un);break;
        }


    return new_data;
  }

};


}}


#endif




