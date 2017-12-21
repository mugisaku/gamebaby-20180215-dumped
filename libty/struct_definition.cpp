#include"struct_definition.hpp"



namespace ty{
namespace ty_types{


void
struct_definition::
append(const type_info&  ti, std::string  name) noexcept
{
  size_t  offset = m_size;

  const auto  sz = ti.get_size();

    if(sz)
    {
      auto  a = ti.get_align();

        if(a)
        {
          offset = (offset+(sz-1))/a*a;
        }
    }


  m_member_list.emplace_back(ti,name,offset);

  m_size  = offset+sz;
  m_align = std::max(m_align,ti.get_align());
}


void
struct_definition::
finalize() noexcept
{
    if(m_size && m_align)
    {
      m_size = (m_size+(m_align-1))/m_align*m_align;
    }
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




