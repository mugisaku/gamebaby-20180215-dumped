#include"union_definition.hpp"
#include<algorithm>



namespace ty{
namespace ty_types{


void
union_definition::
append(const type_info&  ti, std::string  name) noexcept
{
  m_declaration_list.emplace_back(ti,name);

  m_size  = std::max(m_size ,ti.get_size() );
  m_align = std::max(m_align,ti.get_align());
}


void
union_definition::
print(FILE*  f) const noexcept
{
    for(auto&  decl: m_declaration_list)
    {
      decl.print(f,0);

      fprintf(f,"\n");
    }
}


}
}




