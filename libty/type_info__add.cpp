#include"type_info_PRIVATE.hpp"



namespace ty{
namespace types{


type_info
type_info::
add_const() const noexcept
{
    if(is_const())
    {
      return *this;
    }

  else
    if(is_volatile())
    {
      return remove_volatile().add_const_volatile();
    }


  std::string  new_id("C");

  new_id += get_id();

  return type_info(type_kind::const_qualified,new_id,*this,1);
}


type_info
type_info::
add_volatile() const noexcept
{
    if(is_const())
    {
      return remove_const().add_const_volatile();
    }

  else
    if(is_volatile())
    {
      return *this;
    }


  std::string  new_id("V");

  new_id += get_id();

  return type_info(type_kind::volatile_qualified,new_id,*this,1);
}


type_info
type_info::
add_const_volatile() const noexcept
{
    if(is_const_volatile())
    {
      return *this;
    }

  else
    if(is_const())
    {
      return remove_const().add_const_volatile();
    }

  else
    if(is_volatile())
    {
      return remove_volatile().add_const_volatile();
    }


  std::string  new_id("CV");

  new_id += get_id();

  return type_info(type_kind::const_volatile_qualified,new_id,*this,1);
}


type_info
type_info::
add_pointer() const noexcept
{
  std::string  new_id("p");

  new_id += get_id();

  return type_info(type_kind::pointer,new_id,*this,1);
}


type_info
type_info::
add_reference() const noexcept
{
    if(is_reference())
    {
      return *this;
    }


  std::string  new_id("r");

  new_id += get_id();

  return type_info(type_kind::reference,new_id,*this,1);
}


}}




