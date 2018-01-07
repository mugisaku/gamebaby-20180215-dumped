#include"space.hpp"
#include"block.hpp"



namespace ipre{
namespace ipre_types{




const ty::type_decl*
space::
find_type_decl(gbstd::string_view  name) const noexcept
{
    for(auto&  decl: m_type_decl_list)
    {
        if(decl.get_name() == name)
        {
          return &decl;
        }
    }


  return m_parent? m_parent->find_type_decl(name):nullptr;
}


const ty::var_decl*
space::
find_var_decl(gbstd::string_view  name) const noexcept
{
    for(auto&  decl: m_var_decl_list)
    {
        if(decl.get_name() == name)
        {
          return &decl;
        }
    }


  return m_parent? m_parent->find_var_decl(name):nullptr;
}


}}




