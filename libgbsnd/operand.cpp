#include"libgbsnd/expr.hpp"
#include"libgbsnd/execution.hpp"
#include<new>


namespace gbsnd{
namespace devices{




operand&
operand::
operator=(uint64_t  i) noexcept
{
  clear();

  m_kind = kind::integer_literal;

  m_data.i = i;

  return *this;
}


operand&
operand::
operator=(gbstd::string&&  s) noexcept
{
  clear();

  m_kind = kind::identifier;

  m_data.s = std::move(s);

  return *this;
}


operand&
operand::
operator=(expr*  e) noexcept
{
  clear();

  m_kind = kind::expression;

  m_data.e = e;

  return *this;
}


operand&
operand::
operator=(const operand&  rhs) noexcept
{
  clear();

  m_kind = rhs.m_kind;

    switch(m_kind)
    {
  case(kind::integer_literal):
      m_data.i = rhs.m_data.i;
      break;
  case(kind::identifier):
      new(&m_data.s) gbstd::string(rhs.m_data.s);
      break;
  case(kind::expression):
      m_data.e = new expr(*rhs.m_data.e);
      break;
    }


  return *this;
}


operand&
operand::
operator=(operand&&  rhs) noexcept
{
  clear();

  std::swap(m_kind,rhs.m_kind);

    switch(m_kind)
    {
  case(kind::integer_literal):
      m_data.i = rhs.m_data.i;
      break;
  case(kind::identifier):
      new(&m_data.s) gbstd::string(std::move(rhs.m_data.s));
      break;
  case(kind::expression):
      m_data.e = rhs.m_data.e;
    }


  return *this;
}



void
operand::
clear() noexcept
{
    switch(m_kind)
    {
  case(kind::integer_literal):
      break;
  case(kind::identifier):
      m_data.s.~basic_string();
      break;
  case(kind::expression):
      delete m_data.e;
    }


  m_kind = kind::null;
}


value
operand::
evaluate(const execution_context&  ctx) const noexcept
{
    switch(m_kind)
    {
  case(kind::integer_literal):
      return value(m_data.i);
      break;
  case(kind::identifier):
      {
        return *ctx.seek_value(m_data.s);
      }
      break;
  case(kind::expression):
      return m_data.e->evaluate(ctx);
      break;
    }


  return value();
}


}}




