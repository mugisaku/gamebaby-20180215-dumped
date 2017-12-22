#include"array_def.hpp"



namespace ty{
namespace ty_types{


void
array_def::
set(const type_info&  ti, size_t  n) noexcept
{
  m_element_type_info  = ti;
  m_number_of_elements =  n;
}


void
array_def::
print(FILE*  f) const noexcept
{
  m_element_type_info.print(f);

  fprintf(f,"[%zu]",m_number_of_elements);
}


}
}




