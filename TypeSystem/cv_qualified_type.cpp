#include"cv_qualified_type.hpp"
#include"type_table.hpp"




namespace ts{
namespace types{


const type&
cv_qualified_type::
get_type() const noexcept
{
  return (get_name().empty()? type_tables::get_type_by_index(m_type_index)
                            : type_tables::get_type_by_name(get_name()));
}




}}




