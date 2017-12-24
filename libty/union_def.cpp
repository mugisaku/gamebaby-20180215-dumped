#include"union_def.hpp"
#include<algorithm>



namespace ty{
namespace ty_types{


void
union_def::
append(const type_decl&  td, std::string  name) noexcept
{
  m_decl_list.emplace_back(td,name);

  m_size  = std::max(m_size ,td.get_info().get_size() );
  m_align = std::max(m_align,td.get_info().get_align());
}


void
union_def::
print(FILE*  f) const noexcept
{
    for(auto&  decl: m_decl_list)
    {
      print_indent(f);

      decl.print(f);

      fprintf(f,"\n");
    }
}


}
}




