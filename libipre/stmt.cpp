#include"stmt.hpp"
#include<new>



namespace ipre{
namespace ipre_types{




stmt::
stmt(const ty::type_decl&  td, bool  is_def) noexcept:
m_kind(is_def? kind::type_def:kind::type_decl)
{
  new(&m_data) ty::type_decl(td);
}


stmt&
stmt::
operator=(const stmt&   rhs) noexcept
{
    if(&rhs != this)
    {
      clear();

      m_kind = rhs.m_kind;

        switch(m_kind)
        {
      case(kind::type_decl):
      case(kind::type_def):
          new(&m_data) ty::type_decl(rhs.m_data.td);
          break;
        }
    }


  return *this;
}


stmt&
stmt::
operator=(stmt&&  rhs) noexcept
{
    if(&rhs != this)
    {
      clear();

      std::swap(m_kind,rhs.m_kind);

        switch(m_kind)
        {
      case(kind::type_decl):
      case(kind::type_def):
          new(&m_data) ty::type_decl(std::move(rhs.m_data.td));
          break;
        }
    }


  return *this;
}



void
stmt::
clear() noexcept
{
    switch(m_kind)
    {
  case(kind::type_decl):
  case(kind::type_def):
      m_data.td.~type_decl();
      break;
    }


  m_kind = kind::null;
}


}}




