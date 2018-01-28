#include"libgbsnd/object.hpp"
#include"libgbsnd/execution.hpp"
#include<new>


namespace gbsnd{
namespace devices{




value&
value::
operator=(bool  b) noexcept
{
  clear();

  m_kind = kind::integer;

  m_data.i = b? 1:0;

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
operator=(const identifier&  id) noexcept
{
  clear();

  m_kind = kind::identifier;

  new(&m_data) identifier(id);

  return *this;
}


value&
value::
operator=(const property&  pr) noexcept
{
  clear();

  m_kind = kind::property;

  m_data.pr = pr;

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
    if(this != &rhs)
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
      case(kind::identifier):
          new(&m_data) identifier(rhs.m_data.id);
          break;
      case(kind::property):
          m_data.pr = rhs.m_data.pr;
          break;
      case(kind::square_wave):
          m_data.sq = rhs.m_data.sq;
          break;
        }
    }


  return *this;
}


value&
value::
operator=(value&&  rhs) noexcept
{
    if(this != &rhs)
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
      case(kind::identifier):
          new(&m_data) identifier(std::move(rhs.m_data.id));
          break;
      case(kind::property):
          m_data.pr = rhs.m_data.pr;
          break;
      case(kind::square_wave):
          m_data.sq = rhs.m_data.sq;
          break;
        }
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
  case(kind::identifier):
      gbstd::destruct(m_data.id);
      break;
    }


  m_kind = kind::null;
}




value
value::
get_integer_value(const execution_context*  ctx) const noexcept
{
    switch(m_kind)
    {
  case(kind::integer):
      return value(m_data.i);
      break;
  case(kind::reference):
      return m_data.r().get_integer_value(ctx);
      break;
  case(kind::routine):
      break;
  case(kind::identifier):
      return ctx? ctx->get_value(m_data.id.view()).get_integer_value(ctx):value();
      break;
  case(kind::property):
      return m_data.pr.get();
      break;
    }


  return value(0);
}


value
value::
get_routine_value(const execution_context*  ctx) const noexcept
{
    switch(m_kind)
    {
  case(kind::integer):
      break;
  case(kind::reference):
      return m_data.r().get_routine_value(ctx);
      break;
  case(kind::identifier):
      return ctx? ctx->get_value(m_data.id.view()).get_routine_value(ctx):value();
      break;
  case(kind::routine):
      return *this;
      break;
    }


  return value(0);
}


value
value::
get_reference_value(const execution_context*  ctx) const noexcept
{
    switch(m_kind)
    {
  case(kind::integer):
      break;
  case(kind::reference):
      return *this;
      break;
  case(kind::identifier):
      return ctx? ctx->get_value(m_data.id.view()):value();
      break;
  case(kind::routine):
      break;
    }


  return value(0);
}




void
value::
print() const noexcept
{
    switch(m_kind)
    {
  case(kind::null):
      printf("null");
      break;
  case(kind::integer):
      printf("%d",m_data.i);
      break;
  case(kind::reference):
      printf("reference");
      break;
  case(kind::routine):
      m_data.rt->print();
      break;
  case(kind::property):
      printf("property");
      break;
  case(kind::square_wave):
      printf("square_wave");
      break;
    }
}


}}




