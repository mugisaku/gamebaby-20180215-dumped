#include"libgbsnd/expr.hpp"
#include<new>


namespace gbsnd{
namespace devices{




binary_operation&
binary_operation::
operator=(const binary_operation&  rhs) noexcept
{
  clear();

  m_operator = rhs.m_operator;

  m_left_expr  = gbstd::duplicate(rhs.m_left_expr );
  m_right_expr = gbstd::duplicate(rhs.m_right_expr);

  return *this;
}


binary_operation&
binary_operation::
operator=(binary_operation&&  rhs) noexcept
{
  clear();

  std::swap(m_operator  ,rhs.m_operator  );
  std::swap(m_left_expr ,rhs.m_left_expr );
  std::swap(m_right_expr,rhs.m_right_expr);

  return *this;
}


void
binary_operation::
assign(binary_operator  op, expr*  l, expr*  r) noexcept
{
  clear();

  m_operator   = op;
  m_left_expr  =  l;
  m_right_expr =  r;
}


void
binary_operation::
clear() noexcept
{
  delete m_left_expr          ;
         m_left_expr = nullptr;

  delete m_right_expr          ;
         m_right_expr = nullptr;
}


value
binary_operation::
evaluate(const execution_context&  ctx) const noexcept
{
}


}}




