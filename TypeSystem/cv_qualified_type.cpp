#include"cv_qualified_type.hpp"
#include"type_table.hpp"




namespace ts{
namespace types{


const type&
cv_qualified_type::
get_type() const noexcept
{
  return (m_target_type? *m_target_type:type_tables::get_type(m_target_name));
}




}}




