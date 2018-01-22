#include"libgbsnd/expr.hpp"
#include<new>


namespace gbsnd{
namespace devices{




binary_operation&
binary_operation::
operator=(const binary_operation&  rhs) noexcept
{
  clear();

  m_word = rhs.m_word;

  m_left_expr  = gbstd::duplicate(rhs.m_left_expr );
  m_right_expr = gbstd::duplicate(rhs.m_right_expr);

  return *this;
}


binary_operation&
binary_operation::
operator=(binary_operation&&  rhs) noexcept
{
  clear();

  std::swap(m_word      ,rhs.m_word      );
  std::swap(m_left_expr ,rhs.m_left_expr );
  std::swap(m_right_expr,rhs.m_right_expr);

  return *this;
}


void
binary_operation::
assign(operator_word  word, expr*  l, expr*  r) noexcept
{
  clear();

  m_word       = word;
  m_left_expr  =    l;
  m_right_expr =    r;
}


void
binary_operation::
reset(expr*  l, expr*  r) noexcept
{
  clear();

  m_left_expr  = l;
  m_right_expr = r;
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


void
binary_operation::
print() const noexcept
{
    if(m_left_expr)
    {
      m_left_expr->print();
    }


  short_string  ss(m_word);

  printf("%s",ss.data());

    if(m_right_expr)
    {
      m_right_expr->print();
    }
}


}}




