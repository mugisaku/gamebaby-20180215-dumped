#include"type_info_PRIVATE.hpp"



namespace ty{
namespace ty_types{



type_info
type_info::
remove_const() const noexcept
{
  return  is_const()? type_info(m_data->clone(m_data->m_qualification_flags&volatile_flag))
        : *this;
}


type_info
type_info::
remove_volatile() const noexcept
{
  return  is_volatile()? type_info(m_data->clone(m_data->m_qualification_flags&const_flag))
        : *this;
}


type_info
type_info::
remove_const_volatile() const noexcept
{
  return (is_const() || is_volatile())? type_info(m_data->clone(0))
        : *this;
}


type_info  type_info::remove_pointer() const noexcept{return is_pointer()? m_data->m_set.ti:*this;}


type_info
type_info::
remove_reference() const noexcept
{
  return (is_reference() || is_rvalue_reference())? m_data->m_set.ti:*this;
}




}}




