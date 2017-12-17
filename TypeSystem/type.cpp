#include"type.hpp"
#include"type_table.hpp"




namespace ts{
namespace types{




size_t
type::
get_size() const noexcept
{
  return is_simple()? m_data.simple_type.get_size():0;
}


size_t
type::
get_align() const noexcept
{
  return is_simple()? m_data.simple_type.get_size():0;
}


void
type::
print_id(char*  buf, size_t  bufsz) const noexcept
{
  
}




}}




