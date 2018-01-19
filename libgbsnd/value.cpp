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
operator=(const routine&  rt) noexcept
{
  clear();

  m_kind = kind::routine;

  m_data.rt = &rt;

  return *this;
}


value&
value::
operator=(square_wave&  sq) noexcept
{
  clear();

  m_kind = kind::square_wave;

  m_data.sq = &sq;

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
  case(kind::routine):
      m_data.rt = rhs.m_data.rt;
      break;
  case(kind::square_wave):
      m_data.sq = rhs.m_data.sq;
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
  case(kind::routine):
      m_data.rt = rhs.m_data.rt;
      break;
  case(kind::square_wave):
      m_data.sq = rhs.m_data.sq;
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
  case(kind::routine):
      break;
  case(kind::square_wave):
      break;
    }


  m_kind = kind::null;
}


}}




