#include"struct_def.hpp"



namespace ty{
namespace ty_types{


void
struct_def::
append(const type_info&  ti, std::string  name) noexcept
{
  size_t  offset = m_size;

  const auto  sz = ti.get_size();

  offset = get_aligned_offset(offset,ti.get_align());

  m_member_list.emplace_back(ti,name,offset);

  m_size  = offset+sz;
  m_align = std::max(m_align,ti.get_align());
}


void
struct_def::
print(FILE*  f) const noexcept
{
    for(auto&  decl: m_member_list)
    {
      print_indent(f);

      decl.print(f);

      fprintf(f,"\n");
    }
}


}
}




