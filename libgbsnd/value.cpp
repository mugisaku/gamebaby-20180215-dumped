#include"libgbsnd/object.hpp"
#include<new>


namespace gbsnd{
namespace devices{




value&
value::
operator=(int  i) noexcept
{
  clear();

  m_kind = kind::integer;

  m_data.i = i;

  return *this;
}


value&
value::
operator=(reference  r) noexcept
{
  clear();

  m_kind = kind::reference;

  m_data.r = r;

  return *this;
}


value&
value::
operator=(const value&  rhs) noexcept
{
  clear();

  m_kind = rhs.m_kind;

    switch(m_kind)
    {
  case(kind::integer):
      m_data.i = rhs.m_data.i;
      break;
  case(kind::reference):
      m_data.r = rhs.m_data.r;
      break;
    }


  return *this;
}


value&
value::
operator=(value&&  rhs) noexcept
{
  clear();

  std::swap(m_kind,rhs.m_kind);

    switch(m_kind)
    {
  case(kind::integer):
      m_data.i = rhs.m_data.i;
      break;
  case(kind::reference):
      m_data.r = rhs.m_data.r;
      break;
    }


  return *this;
}



void
value::
clear() noexcept
{
    switch(m_kind)
    {
  case(kind::integer):
      break;
  case(kind::reference):
      break;
    }


  m_kind = kind::null;
}


}}




