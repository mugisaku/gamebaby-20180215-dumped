#include"libgbsnd/expr.hpp"
#include"libgbsnd/execution.hpp"
#include<new>


namespace gbsnd{
namespace devices{




operand&
operand::
operator=(undefined  u) noexcept
{
  clear();

  m_kind = kind::undefined_literal;

  return *this;
}


operand&
operand::
operator=(bool  b) noexcept
{
  clear();

  m_kind = kind::boolean_literal;

  m_data.b = b;

  return *this;
}


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
operator=(const identifier&  id) noexcept
{
    if(id == gbstd::string_view("undefined"))
    {
      *this = undefined();
    }

  else
    if(id == gbstd::string_view("true"))
    {
      *this = true;
    }

  else
    if(id == gbstd::string_view("false"))
    {
      *this = false;
    }

  else
    {
      clear();

      m_kind = kind::identifier;

      new(&m_data) identifier(id);
    }


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
  case(kind::boolean_literal):
      m_data.b = rhs.m_data.b;
      break;
  case(kind::integer_literal):
      m_data.i = rhs.m_data.i;
      break;
  case(kind::identifier):
      new(&m_data) identifier(rhs.m_data.id);
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
  case(kind::boolean_literal):
      m_data.b = rhs.m_data.b;
      break;
  case(kind::integer_literal):
      m_data.i = rhs.m_data.i;
      break;
  case(kind::identifier):
      new(&m_data) identifier(std::move(rhs.m_data.id));
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
      gbstd::destruct(m_data.id);
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
  case(kind::undefined_literal):
      return value(undefined());
      break;
  case(kind::boolean_literal):
      return value(m_data.b);
      break;
  case(kind::integer_literal):
      return value(static_cast<int>(m_data.i));
      break;
  case(kind::identifier):
      {
        return *ctx.seek_value(m_data.id.view());
      }
      break;
  case(kind::expression):
      return m_data.e->evaluate(ctx);
      break;
    }


  return value();
}


void
operand::
print() const noexcept
{
    switch(m_kind)
    {
  case(kind::undefined_literal):
      printf("undefined");
      break;
  case(kind::boolean_literal):
      printf("%s",m_data.b? "true":"false");
      break;
  case(kind::integer_literal):
      printf("%lu",m_data.i);
      break;
  case(kind::identifier):
      printf("%s",m_data.id.data());
      break;
  case(kind::expression):
      m_data.e->print();
      break;
    }
}


}}




