#include"libgbsnd/expr.hpp"
#include<new>


namespace gbsnd{
namespace devices{




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
      auto  v = m_expr.evaluate(ctx).convert_to_boolean();

        if(v)
        {
          return value(!v.get_boolean());
        }
    }

  else
    if(m_word == operator_word("-"))
    {
      auto  v = m_expr.evaluate(ctx).convert_to_integer();

        if(v)
        {
          return value(-v.get_integer());
        }
    }

  else
    if(m_word == operator_word("~"))
    {
      auto  v = m_expr.evaluate(ctx).convert_to_integer();

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
      m_expr.print();
    }


    if(is_postfix())
    {
      short_string  ss(m_word);

      printf("%s",ss.data());
    }
}


}}




