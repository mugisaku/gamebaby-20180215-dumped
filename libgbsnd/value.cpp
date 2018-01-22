#include"libgbsnd/object.hpp"
#include<new>


namespace gbsnd{
namespace devices{




value&
value::
operator=(undefined  u) noexcept
{
  clear();

  m_kind = kind::undefined;

  return *this;
}


value&
value::
operator=(bool  b) noexcept
{
  clear();

  m_kind = kind::boolean;

  m_data.b = b;

  return *this;
}


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
  case(kind::boolean):
      m_data.b = rhs.m_data.b;
      break;
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
  case(kind::boolean):
      m_data.b = rhs.m_data.b;
      break;
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




value
value::
convert_to_integer() const noexcept
{
    switch(m_kind)
    {
  case(kind::undefined):
      break;
  case(kind::integer):
      return value(m_data.i);
      break;
  case(kind::reference):
      return m_data.r().get_value().convert_to_integer();
      break;
  case(kind::routine):
      break;
  case(kind::square_wave):
      break;
    }


  return value(undefined());
}


value
value::
convert_to_boolean() const noexcept
{
    switch(m_kind)
    {
  case(kind::undefined):
      return value(false);
      break;
  case(kind::integer):
      return value(m_data.i? true:false);
      break;
  case(kind::reference):
      return m_data.r().get_value().convert_to_boolean();
      break;
  case(kind::routine):
      return value(true);
      break;
  case(kind::square_wave):
      return value(true);
      break;
    }


  return value(undefined());
}


value
value::
convert_to_routine() const noexcept
{
    switch(m_kind)
    {
  case(kind::undefined):
      break;
  case(kind::integer):
      break;
  case(kind::reference):
      return m_data.r().get_value().convert_to_routine();
      break;
  case(kind::routine):
      return *this;
      break;
  case(kind::square_wave):
      break;
    }


  return value(undefined());
}


value
value::
convert_to_square_wave() const noexcept
{
    switch(m_kind)
    {
  case(kind::undefined):
      break;
  case(kind::integer):
      break;
  case(kind::reference):
      return m_data.r().get_value().convert_to_square_wave();
      break;
  case(kind::routine):
      break;
  case(kind::square_wave):
      return *this;
      break;
    }


  return value(undefined());
}




}}




