#include"libgbsnd/expr.hpp"
#include<new>


namespace gbsnd{
namespace devices{




unary_operation&
unary_operation::
operator=(const unary_operation&  rhs) noexcept
{
  clear();

  m_kind = rhs.m_kind;
  m_word = rhs.m_word;

  m_expr = gbstd::duplicate(rhs.m_expr);

  return *this;
}


unary_operation&
unary_operation::
operator=(unary_operation&&  rhs) noexcept
{
  clear();

  std::swap(m_kind,rhs.m_kind);
  std::swap(m_word,rhs.m_word);
  std::swap(m_expr,rhs.m_expr);

  return *this;
}


void
unary_operation::
assign(operator_word  word, expr*  expr) noexcept
{
  clear();

  m_word = word;
  m_expr = expr;
}


void
unary_operation::
reset(expr*  expr) noexcept
{
  clear();

  m_expr = expr;
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
    if(m_word == operator_word("*"))
    {
    }

  else
    if(m_word == operator_word("!"))
    {
      auto  v = m_expr->evaluate(ctx).convert_to_boolean();

        if(v)
        {
          return value(!v.get_boolean());
        }
    }

  else
    if(m_word == operator_word("-"))
    {
      auto  v = m_expr->evaluate(ctx).convert_to_integer();

        if(v)
        {
          return value(-v.get_integer());
        }
    }

  else
    if(m_word == operator_word("~"))
    {
      auto  v = m_expr->evaluate(ctx).convert_to_integer();

        if(v)
        {
          return value(~v.get_integer());
        }
    }

  else
    if(m_word == operator_word("&"))
    {
    }


  return value(undefined());
}


void
unary_operation::
print() const noexcept
{
    if(is_prefix())
    {
      short_string  ss(m_word);

      printf("%s",ss.data());
    }


    if(m_expr)
    {
      m_expr->print();
    }


    if(is_postfix())
    {
      short_string  ss(m_word);

      printf("%s",ss.data());
    }
}


}}




