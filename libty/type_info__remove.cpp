#include"type_info_PRIVATE.hpp"



namespace ty{
namespace ty_types{



type_info
type_info::
remove_const() const noexcept
{
  return  is_const()         ? m_data->definition.ti
        : is_const_volatile()? m_data->definition.ti.add_volatile()
        : *this;
}


type_info
type_info::
remove_volatile() const noexcept
{
  return  is_volatile()      ? m_data->definition.ti
        : is_const_volatile()? m_data->definition.ti.add_const()
        : *this;
}


type_info
type_info::
remove_const_volatile() const noexcept
{
  return  is_const()         ? m_data->definition.ti
        : is_volatile()      ? m_data->definition.ti
        : is_const_volatile()? m_data->definition.ti
        : *this;
}


type_info  type_info::remove_pointer()   const noexcept{return   is_pointer()? m_data->definition.ti:*this;}
type_info  type_info::remove_reference() const noexcept{return is_reference()? m_data->definition.ti:*this;}




}}




