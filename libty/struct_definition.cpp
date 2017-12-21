#include"struct_definition.hpp"



namespace ty{
namespace ty_types{


void
struct_definition::
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
struct_definition::
finalize() noexcept
{
  m_size = get_aligned_offset(m_size,m_align);
}


void
struct_definition::
print(FILE*  f) const noexcept
{
    for(auto&  decl: m_member_list)
    {
      decl.print(f);

      fprintf(f,"\n");
    }
}


}
}




