#include"type_info.hpp"
#include"type_table.hpp"



namespace ts{
namespace types{


size_t
type_info::
get_size() const noexcept
{
    switch(m_kind)
    {
  case(type_kind::signed_integral): return m_data.sint_info.get_size();
  case(type_kind::unsigned_integral): return m_data.uint_info.get_size();
  case(type_kind::boolean): return m_data.bool_info.get_size();
  case(type_kind::void_): return 0;
  case(type_kind::null_pointer): return pointer_type_size;
  case(type_kind::generic_pointer): return pointer_type_size;
  case(type_kind::pointer): return pointer_type_size;
  case(type_kind::reference): return get_pointer_info().get_target().get_size();
  case(type_kind::array): return get_array_info().get_target().get_size();
    }
}


size_t
type_info::
get_align() const noexcept
{
    switch(m_kind)
    {
  case(type_kind::signed_integral):
  case(type_kind::unsigned_integral):
  case(type_kind::boolean):
  case(type_kind::void_):
  case(type_kind::null_pointer):
  case(type_kind::generic_pointer):
  case(type_kind::pointer): return get_size();
  case(type_kind::reference): return get_pointer_info().get_target().get_align();
  case(type_kind::array): return get_array_info().get_target().get_align();
    }
}


const type_info&
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
      return add_const_volatile();
    }


  std::string  new_id("C");
  std::string  new_hid("const ");

  new_id += m_id;
  new_hid += m_hid;

  return append_type_info(type_info(new_id,new_hid,const_qualified_type_info(*this)));
}


const type_info&
type_info::
add_volatile() const noexcept
{
    if(is_const())
    {
      return add_const_volatile();
    }

  else
    if(is_volatile())
    {
      return *this;
    }


  std::string  new_id("V");
  std::string  new_hid("volatile ");

  new_id += m_id;
  new_hid += m_hid;

  return append_type_info(type_info(new_id,new_hid,volatile_qualified_type_info(*this)));
}


const type_info&
type_info::
add_const_volatile() const noexcept
{
    if(is_const_volatile())
    {
      return *this;
    }


  std::string  new_id("CV");
  std::string  new_hid("const volatile ");

  new_id += m_id;
  new_hid += m_hid;

  return append_type_info(type_info(new_id,new_hid,const_volatile_qualified_type_info(*this)));
}


const type_info&
type_info::
add_pointer() const noexcept
{
  std::string  new_id("p");
  std::string  new_hid(m_hid);

  new_id += m_id;
  new_hid += "*";

  return append_type_info(type_info(new_id,new_hid,pointer_type_info(*this)));
}


const type_info&
type_info::
add_reference() const noexcept
{
    if(is_reference())
    {
      return *this;
    }


  std::string  new_id("r");
  std::string  new_hid(m_hid);

  new_id += m_id;
  new_hid += "&";

  return append_type_info(type_info(new_id,new_hid,reference_type_info(*this)));
}


const type_info&
type_info::
make_array(size_t  n) const noexcept
{
  std::string  new_id("a");
  std::string  new_hid(m_hid);

  auto  ns = std::to_string(n);

  new_id += ns;
  new_id += m_id;
  new_hid += "[";
  new_hid += ns;
  new_hid += "]";

  return append_type_info(type_info(new_id,new_hid,array_type_info(*this,n)));
}


}}




