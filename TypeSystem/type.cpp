#include"type.hpp"
#include"type_table.hpp"
#include<cstring>




namespace ts{
namespace types{




size_t
type::
get_size() const noexcept
{
  return is_simple()? get_type_info_by_name(m_data.simple_type.get_name()).get_size():0;
}


size_t
type::
get_align() const noexcept
{
  return is_simple()? get_type_info_by_name(m_data.simple_type.get_name()).get_align():0;
}


void
type::
print_id(char*  buf, size_t  bufsz) const noexcept
{
    if(is_simple())
    {
      auto  id = get_type_info_by_name(m_data.simple_type.get_name()).get_id();

      std::strncpy(buf,id.data(),id.size());
    }
}




}}




