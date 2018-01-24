#include"libgbsnd/expr.hpp"
#include<new>


namespace gbsnd{
namespace devices{




void
binary_operation::
reset(expr&&  l, expr&&  r) noexcept
{
  m_left_expr  = std::move(l);
  m_right_expr = std::move(r);
}


bool
are_both_integer(const value&  a, const value&  b) noexcept
{
  return a.is_integer() && b.is_integer();
}


value
binary_operation::
evaluate(const execution_context&  ctx) const noexcept
{
    if(m_word == operator_word("+"))
    {
      auto  lv =  m_left_expr.evaluate(ctx).convert_to_integer();
      auto  rv = m_right_expr.evaluate(ctx).convert_to_integer();

      return are_both_integer(lv,rv)? value(lv.get_integer()+rv.get_integer()):value(undefined());
    }

  else
    if(m_word == operator_word("-"))
    {
      auto  lv =  m_left_expr.evaluate(ctx).convert_to_integer();
      auto  rv = m_right_expr.evaluate(ctx).convert_to_integer();

      return are_both_integer(lv,rv)? value(lv.get_integer()-rv.get_integer()):value(undefined());
    }

  else
    if(m_word == operator_word("*"))
    {
      auto  lv =  m_left_expr.evaluate(ctx).convert_to_integer();
      auto  rv = m_right_expr.evaluate(ctx).convert_to_integer();

      return are_both_integer(lv,rv)? value(lv.get_integer()*rv.get_integer()):value(undefined());
    }

  else
    if(m_word == operator_word("/"))
    {
      auto  lv =  m_left_expr.evaluate(ctx).convert_to_integer();
      auto  rv = m_right_expr.evaluate(ctx).convert_to_integer();

      auto  ri = rv.get_integer();

      return are_both_integer(lv,rv) && ri? value(lv.get_integer()/ri):value(undefined());
    }

  else
    if(m_word == operator_word("%"))
    {
      auto  lv =  m_left_expr.evaluate(ctx).convert_to_integer();
      auto  rv = m_right_expr.evaluate(ctx).convert_to_integer();

      auto  ri = rv.get_integer();

      return are_both_integer(lv,rv) && ri? value(lv.get_integer()%ri):value(undefined());
    }

  else
    if(m_word == operator_word("<<"))
    {
      auto  lv =  m_left_expr.evaluate(ctx).convert_to_integer();
      auto  rv = m_right_expr.evaluate(ctx).convert_to_integer();

      return are_both_integer(lv,rv)? value(lv.get_integer()<<rv.get_integer()):value(undefined());
    }

  else
    if(m_word == operator_word(">>"))
    {
      auto  lv =  m_left_expr.evaluate(ctx).convert_to_integer();
      auto  rv = m_right_expr.evaluate(ctx).convert_to_integer();

      return are_both_integer(lv,rv)? value(lv.get_integer()>>rv.get_integer()):value(undefined());
    }

  else
    if(m_word == operator_word("|"))
    {
      auto  lv =  m_left_expr.evaluate(ctx).convert_to_integer();
      auto  rv = m_right_expr.evaluate(ctx).convert_to_integer();

      return are_both_integer(lv,rv)? value(lv.get_integer()|rv.get_integer()):value(undefined());
    }

  else
    if(m_word == operator_word("||"))
    {
      auto  lv =  m_left_expr.evaluate(ctx).convert_to_boolean();

        if(lv.is_boolean())
        {
            if(lv.get_boolean())
            {
              return value(true);
            }

          else
            {
              auto  rv =  m_right_expr.evaluate(ctx).convert_to_boolean();

                if(rv.is_boolean())
                {
                  return value(rv.get_boolean());
                }
            }
        }
    }

  else
    if(m_word == operator_word("&"))
    {
      auto  lv =  m_left_expr.evaluate(ctx).convert_to_integer();
      auto  rv = m_right_expr.evaluate(ctx).convert_to_integer();

      return are_both_integer(lv,rv)? value(lv.get_integer()&rv.get_integer()):value(undefined());
    }

  else
    if(m_word == operator_word("&&"))
    {
      auto  lv =  m_left_expr.evaluate(ctx).convert_to_boolean();

        if(lv.is_boolean())
        {
            if(!lv.get_boolean())
            {
              return value(false);
            }

          else
            {
              auto  rv =  m_right_expr.evaluate(ctx).convert_to_boolean();

                if(rv.is_boolean())
                {
                  return value(rv.get_boolean());
                }
            }
        }
    }

  else
    if(m_word == operator_word("^"))
    {
      auto  lv =  m_left_expr.evaluate(ctx).convert_to_integer();
      auto  rv = m_right_expr.evaluate(ctx).convert_to_integer();

      return are_both_integer(lv,rv)? value(lv.get_integer()^rv.get_integer()):value(undefined());
    }

  else
    if(m_word == operator_word("=="))
    {
      auto  lv =  m_left_expr.evaluate(ctx).convert_to_integer();
      auto  rv = m_right_expr.evaluate(ctx).convert_to_integer();

      return are_both_integer(lv,rv)? value(lv.get_integer() == rv.get_integer()):value(undefined());
    }

  else
    if(m_word == operator_word("!="))
    {
      auto  lv =  m_left_expr.evaluate(ctx).convert_to_integer();
      auto  rv = m_right_expr.evaluate(ctx).convert_to_integer();

      return are_both_integer(lv,rv)? value(lv.get_integer() != rv.get_integer()):value(undefined());
    }

  else
    if(m_word == operator_word("<"))
    {
      auto  lv =  m_left_expr.evaluate(ctx).convert_to_integer();
      auto  rv = m_right_expr.evaluate(ctx).convert_to_integer();

      return are_both_integer(lv,rv)? value(lv.get_integer() < rv.get_integer()):value(undefined());
    }

  else
    if(m_word == operator_word("<="))
    {
      auto  lv =  m_left_expr.evaluate(ctx).convert_to_integer();
      auto  rv = m_right_expr.evaluate(ctx).convert_to_integer();

      return are_both_integer(lv,rv)? value(lv.get_integer() <= rv.get_integer()):value(undefined());
    }

  else
    if(m_word == operator_word(">"))
    {
      auto  lv =  m_left_expr.evaluate(ctx).convert_to_integer();
      auto  rv = m_right_expr.evaluate(ctx).convert_to_integer();

      return are_both_integer(lv,rv)? value(lv.get_integer() > rv.get_integer()):value(undefined());
    }

  else
    if(m_word == operator_word(">="))
    {
      auto  lv =  m_left_expr.evaluate(ctx).convert_to_integer();
      auto  rv = m_right_expr.evaluate(ctx).convert_to_integer();

      return are_both_integer(lv,rv)? value(lv.get_integer() >= rv.get_integer()):value(undefined());
    }

  else
    if(m_word == operator_word(","))
    {
      auto  lv =  m_left_expr.evaluate(ctx);

      return m_right_expr.evaluate(ctx);
    }

  else
    if(m_word == operator_word("."))
    {
      auto  lv = m_left_expr.evaluate(ctx);

        if(lv.is_reference() && m_right_expr.is_operand())
        {
          auto&  o = m_right_expr.get_operand();

            if(o.is_identifier())
            {
              auto&  obj = lv.get_reference()();

              return value(property(obj,square_wave::find_accessor(o.get_identifier().view())));
            }
        }


      printf("メンバアクセスエラー");
    }

  else
    if(m_word == operator_word("->"))
    {
    }

  else
    if(m_word == operator_word("="))
    {
    }

  else
    if(m_word == operator_word("+="))
    {
    }

  else
    if(m_word == operator_word("-="))
    {
    }

  else
    if(m_word == operator_word("*="))
    {
    }

  else
    if(m_word == operator_word("/="))
    {
    }

  else
    if(m_word == operator_word("%="))
    {
    }

  else
    if(m_word == operator_word("<<="))
    {
    }

  else
    if(m_word == operator_word(">>="))
    {
    }

  else
    if(m_word == operator_word("|="))
    {
    }

  else
    if(m_word == operator_word("&="))
    {
    }

  else
    if(m_word == operator_word("^="))
    {
    }


  return value(undefined());
}


void
binary_operation::
print() const noexcept
{
    if(m_left_expr)
    {
      m_left_expr.print();
    }


  short_string  ss(m_word);

  printf("%s",ss.data());

    if(m_right_expr)
    {
      m_right_expr.print();
    }
}


}}




