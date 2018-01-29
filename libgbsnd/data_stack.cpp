#include"libgbsnd/expr.hpp"
#include"libgbsnd/script.hpp"
#include<new>


namespace gbsnd{
namespace devices{




const value&
data_stack::
operate_prefix_unary(operator_word  opw, const execution_context*  ctx) noexcept
{
    if(opw == gbstd::string_view(""))
    {
    }


  return top();
}


const value&
data_stack::
operate_postfix_unary(operator_word  opw, const execution_context*  ctx) noexcept
{
    if(opw == gbstd::string_view(""))
    {
    }


  return top();
}


const value&
data_stack::
operate_binary(operator_word  opw, const execution_context*  ctx) noexcept
{
    if(opw == gbstd::string_view("||"))
    {
      auto  rv = pop().get_integer_value(ctx);

        if(rv.get_integer())
        {
          top() = value(true);
        }

      else
        {
          auto  lv = top().get_integer_value(ctx);

          top() = value(lv.get_integer());
        }
    }

  else
    if(opw == gbstd::string_view("&&"))
    {
      auto  rv = pop().get_integer_value(ctx);

        if(rv.get_integer())
        {
          auto  lv = top().get_integer_value(ctx);

          top() = value(lv.get_integer());
        }

      else
        {
          top() = value(false);
        }
    }




    if(opw == gbstd::string_view("+"))
    {
      auto  rv = pop().get_integer_value(ctx);
      auto  lv = top().get_integer_value(ctx);

      top() = value(lv.get_integer()+
                    rv.get_integer());
    }

  else
    if(opw == gbstd::string_view("-"))
    {
      auto  rv = pop().get_integer_value(ctx);
      auto  lv = top().get_integer_value(ctx);

      top() = value(lv.get_integer()-
                    rv.get_integer());
    }

  else
    if(opw == gbstd::string_view("*"))
    {
      auto  rv = pop().get_integer_value(ctx);
      auto  lv = top().get_integer_value(ctx);

      top() = value(lv.get_integer()*
                    rv.get_integer());
    }

  else
    if(opw == gbstd::string_view("/"))
    {
      auto  rv = pop().get_integer_value(ctx);
      auto  lv = top().get_integer_value(ctx);

      auto  i = rv.get_integer();

        if(!i)
        {
          printf("ゼロ除算\n");
        }

      else
        {
          top() = value(lv.get_integer()/i);
        }
    }

  else
    if(opw == gbstd::string_view("%"))
    {
      auto  rv = pop().get_integer_value(ctx);
      auto  lv = top().get_integer_value(ctx);

      auto  i = rv.get_integer();

        if(!i)
        {
          printf("ゼロ除算\n");
        }

      else
        {
          top() = value(lv.get_integer()%i);
        }
    }

  else
    if(opw == gbstd::string_view("<<"))
    {
      auto  rv = pop().get_integer_value(ctx);
      auto  lv = top().get_integer_value(ctx);

      top() = value(lv.get_integer()<<
                    rv.get_integer());
    }

  else
    if(opw == gbstd::string_view(">>"))
    {
      auto  rv = pop().get_integer_value(ctx);
      auto  lv = top().get_integer_value(ctx);

      top() = value(lv.get_integer()>>
                    rv.get_integer());
    }

  else
    if(opw == gbstd::string_view("|"))
    {
      auto  rv = pop().get_integer_value(ctx);
      auto  lv = top().get_integer_value(ctx);

      top() = value(lv.get_integer()|
                    rv.get_integer());
    }

  else
    if(opw == gbstd::string_view("&"))
    {
      auto  rv = pop().get_integer_value(ctx);
      auto  lv = top().get_integer_value(ctx);

      top() = value(lv.get_integer()&
                    rv.get_integer());
    }

  else
    if(opw == gbstd::string_view("^"))
    {
      auto  rv = pop().get_integer_value(ctx);
      auto  lv = top().get_integer_value(ctx);

      top() = value(lv.get_integer()^
                    rv.get_integer());
    }

  else
    if(opw == gbstd::string_view("=="))
    {
      auto  rv = pop().get_integer_value(ctx);
      auto  lv = top().get_integer_value(ctx);

      top() = value(lv.get_integer() ==
                    rv.get_integer());
    }

  else
    if(opw == gbstd::string_view("!="))
    {
      auto  rv = pop().get_integer_value(ctx);
      auto  lv = top().get_integer_value(ctx);

      top() = value(lv.get_integer() !=
                    rv.get_integer());
    }

  else
    if(opw == gbstd::string_view("<"))
    {
      auto  rv = pop().get_integer_value(ctx);
      auto  lv = top().get_integer_value(ctx);

      top() = value(lv.get_integer() <
                    rv.get_integer());
    }

  else
    if(opw == gbstd::string_view("<="))
    {
      auto  rv = pop().get_integer_value(ctx);
      auto  lv = top().get_integer_value(ctx);

      top() = value(lv.get_integer() <=
                    rv.get_integer());
    }

  else
    if(opw == gbstd::string_view(">"))
    {
      auto  rv = pop().get_integer_value(ctx);
      auto  lv = top().get_integer_value(ctx);

      top() = value(lv.get_integer() >
                    rv.get_integer());
    }

  else
    if(opw == gbstd::string_view(">="))
    {
      auto  rv = pop().get_integer_value(ctx);
      auto  lv = top().get_integer_value(ctx);

      top() = value(lv.get_integer() >=
                    rv.get_integer());
    }

  else
    if(opw == gbstd::string_view("="))
    {
      auto   rv = pop().get_integer_value(ctx);
      auto&  lv = top();

      int  i = rv.get_integer();

        if(lv.is_property())
        {
          lv.get_property().set(i);
        }

      else
        if(lv.is_reference())
        {
         auto&  obj = lv.get_reference()();

            if(obj.is_integer())
            {
              obj.get_integer() = i;
            }
        }

      else
        {
          printf("=, 左辺が参照でもプロパティでもない\n");
        }
    }

  else
    if(opw == gbstd::string_view("+="))
    {
    }

  else
    if(opw == gbstd::string_view("-="))
    {
    }

  else
    if(opw == gbstd::string_view("*="))
    {
    }

  else
    if(opw == gbstd::string_view("/="))
    {
    }

  else
    if(opw == gbstd::string_view("%="))
    {
    }

  else
    if(opw == gbstd::string_view("<<="))
    {
    }

  else
    if(opw == gbstd::string_view(">>="))
    {
    }

  else
    if(opw == gbstd::string_view("|="))
    {
    }

  else
    if(opw == gbstd::string_view("&="))
    {
    }

  else
    if(opw == gbstd::string_view("^="))
    {
    }

  else
    if(opw == gbstd::string_view("::"))
    {
    }

  else
    if(opw == gbstd::string_view("."))
    {
      auto&  rv = pop();
      auto   lv = top().get_reference_value(ctx);

        if(!rv.is_identifier())
        {
          printf("右辺が識別子ではない\n");
        }

      else
        if(!lv.is_reference())
        {
          printf(".%s\n",rv.get_identifier().view().data());

          printf("左辺が参照ではない\n");

          lv.print();
        }

      else
        {
          top() = value(lv.get_reference().get_property(rv.get_identifier()));
        }
    }

  else
    if(opw == gbstd::string_view("->"))
    {
    }

  else
    if(opw == gbstd::string_view(","))
    {
    }


  return top();
}




}}




