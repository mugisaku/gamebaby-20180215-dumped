#include"libgbsnd/expr.hpp"
#include<new>


namespace gbsnd{
namespace devices{




unary_operation&
unary_operation::
operator=(const unary_operation&  rhs) noexcept
{
  clear();

  m_operator = rhs.m_operator;

  m_expr = duplicate(rhs.m_expr);

  return *this;
}


unary_operation&
unary_operation::
operator=(unary_operation&&  rhs) noexcept
{
  clear();

  std::swap(m_operator,rhs.m_operator);
  std::swap(m_expr    ,rhs.m_expr    );

  return *this;
}


void
unary_operation::
assign(unary_operator  op, expr*  expr) noexcept
{
  clear();

  m_operator = op;
  m_expr     = expr;
}


void
unary_operation::
clear() noexcept
{
  delete m_expr          ;
         m_expr = nullptr;
}


value
unary_operation::
evaluate(const execution_context&  ctx) const noexcept
{
}


}}




