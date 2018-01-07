#include"type_info_PRIVATE.hpp"



namespace ty{
namespace ty_types{


type_info
type_info::
add_const() const noexcept
{
    if(is_const())
    {
      return *this;
    }


  return type_info(m_data->clone(m_data->m_qualification_flags|const_flag));
}


type_info
type_info::
add_volatile() const noexcept
{
    if(is_volatile())
    {
      return *this;
    }


  return type_info(m_data->clone(m_data->m_qualification_flags|volatile_flag));
}


type_info
type_info::
add_const_volatile() const noexcept
{
    if(is_const_volatile())
    {
      return *this;
    }


  return type_info(m_data->clone(const_volatile_flags));
}


type_info
type_info::
add_pointer() const noexcept
{
  gbstd::string  new_id("p");

  new_id += get_id();

  return type_info(new_id,type_kind::pointer,*this);
}


type_info
type_info::
add_reference() const noexcept
{
    if(is_reference())
    {
      return *this;
    }


  gbstd::string  new_id("r");

  new_id += get_id();

  return type_info(new_id,type_kind::reference,*this);
}


type_info
type_info::
add_rvalue_reference() const noexcept
{
    if(is_reference() || is_rvalue_reference())
    {
      return *this;
    }


  gbstd::string  new_id("rr");

  new_id += get_id();

  return type_info(new_id,type_kind::rvalue_reference,*this);
}


}}




