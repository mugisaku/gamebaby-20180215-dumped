#include"array_definition.hpp"



namespace ty{
namespace ty_types{


void
array_definition::
set(const type_info&  ti, size_t  n) noexcept
{
  m_element_type_info  = ti;
  m_number_of_elements =  n;
}


}
}




