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
print(FILE*  f, size_t  offset_base) const noexcept
{
    for(auto&  decl: m_member_list)
    {
      decl.print(f,offset_base);

      fprintf(f,"\n");
    }
}


}
}




