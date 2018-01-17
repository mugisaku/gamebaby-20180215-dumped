#include"libgbsnd/expr.hpp"
#include"libgbsnd/execution.hpp"
#include<new>


namespace gbsnd{
namespace devices{




expr&
expr::
operator=(operand&&  o) noexcept
{
  clear();

  m_kind = kind::operand;

  m_data.o = std::move(o);

  return *this;
}


expr&
expr::
operator=(unary_operation&&  unop) noexcept
{
  clear();

  m_kind = kind::unary_operation;

  m_data.unop = std::move(unop);

  return *this;
}


expr&
expr::
operator=(binary_operation&&  binop) noexcept
{
  clear();

  m_kind = kind::binary_operation;

  m_data.binop = std::move(binop);

  return *this;
}


expr&
expr::
operator=(const expr&  rhs) noexcept
{
  clear();

  m_kind = rhs.m_kind;

    switch(m_kind)
    {
  case(kind::operand):
      new(&m_data) operand(rhs.m_data.o);
      break;
  case(kind::unary_operation):
      new(&m_data.unop) unary_operation(rhs.m_data.unop);
      break;
  case(kind::binary_operation):
      new(&m_data.binop) binary_operation(rhs.m_data.binop);
      break;
    }


  return *this;
}


expr&
expr::
operator=(expr&&  rhs) noexcept
{
  clear();

  std::swap(m_kind,rhs.m_kind);

    switch(m_kind)
    {
  case(kind::operand):
      new(&m_data) operand(std::move(rhs.m_data.o));
      break;
  case(kind::unary_operation):
      new(&m_data.unop) unary_operation(std::move(rhs.m_data.unop));
      break;
  case(kind::binary_operation):
      new(&m_data.binop) binary_operation(std::move(rhs.m_data.binop));
      break;
    }


  return *this;
}



void
expr::
clear() noexcept
{
    switch(m_kind)
    {
  case(kind::operand):
      m_data.o.~operand();
      break;
  case(kind::unary_operation):
      m_data.unop.~unary_operation();
      break;
  case(kind::binary_operation):
      m_data.binop.~binary_operation();
      break;
    }


  m_kind = kind::null;
}


value
expr::
evaluate(const execution_context&  ctx) const noexcept
{
    switch(m_kind)
    {
  case(kind::operand):
      return m_data.o.evaluate(ctx);
      break;
  case(kind::unary_operation):
      return m_data.unop.evaluate(ctx);
      break;
  case(kind::binary_operation):
      return m_data.binop.evaluate(ctx);
      break;
    }


  return value();
}


}}




