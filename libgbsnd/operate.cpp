#include"libgbsnd/expr.hpp"
#include"libgbsnd/script.hpp"
#include<new>


namespace gbsnd{
namespace devices{




void
operate_prefix_unary(value&  v, operator_word  opw, const execution_context*  ctx) noexcept
{
  auto  i = v.to_rhs(ctx).get_integer_safely();

    if(opw == gbstd::string_view("!"))
    {
      v = value(!i);
    }

  else
    if(opw == gbstd::string_view("~"))
    {
      v = value(~i);
    }

  else
    if(opw == gbstd::string_view("-"))
    {
      v = value(-i);
    }
}


void
operate_postfix_unary(value&  v, operator_word  opw, const execution_context*  ctx) noexcept
{
    if(opw == gbstd::string_view(""))
    {
    }
}


void
operate_binary(value&  lv, value&  rv, operator_word  opw, const execution_context*  ctx) noexcept
{
    if(opw == gbstd::string_view("||"))
    {
        if(lv.to_rhs(ctx).get_integer_safely())
        {
          lv = value(true);
        }

      else
        {
          lv = value(rv.to_rhs(ctx).get_integer_safely());
        }


      return;
    }

  else
    if(opw == gbstd::string_view("&&"))
    {
        if(lv.to_rhs(ctx).get_integer_safely())
        {
          lv = value(rv.to_rhs(ctx).get_integer_safely());
        }

      else
        {
          lv = value(false);
        }


      return;
    }




  auto  ri = rv.to_rhs(ctx).get_integer_safely();
  auto  li = lv.to_rhs(ctx).get_integer_safely();

       if(opw == gbstd::string_view("+")){lv = value(li+ri);}
  else if(opw == gbstd::string_view("-")){lv = value(li-ri);}
  else if(opw == gbstd::string_view("*")){lv = value(li*ri);}
  else
    if(opw == gbstd::string_view("/"))
    {
        if(!ri)
        {
          printf("div error: ゼロ除算\n");
        }

      else
        {
          lv = value(li/ri);
        }
    }

  else
    if(opw == gbstd::string_view("%"))
    {
        if(!ri)
        {
          printf("rem error: ゼロ除算\n");
        }

      else
        {
          lv = value(li%ri);
        }
    }

  else if(opw == gbstd::string_view("<<")){lv = value(li<<ri);}
  else if(opw == gbstd::string_view(">>")){lv = value(li>>ri);}
  else if(opw == gbstd::string_view("|")) {lv = value(li|ri);}
  else if(opw == gbstd::string_view("&")) {lv = value(li&ri);}
  else if(opw == gbstd::string_view("^")) {lv = value(li^ri);}
  else if(opw == gbstd::string_view("==")){lv = value(li == ri);}
  else if(opw == gbstd::string_view("!=")){lv = value(li != ri);}
  else if(opw == gbstd::string_view("<")) {lv = value(li <  ri);}
  else if(opw == gbstd::string_view("<=")){lv = value(li <= ri);}
  else if(opw == gbstd::string_view(">")) {lv = value(li >  ri);}
  else if(opw == gbstd::string_view(">=")){lv = value(li >= ri);}
  else
    if(opw == gbstd::string_view("::"))
    {
    }

  else
    if(opw == gbstd::string_view("."))
    {
      auto  rhs_lv = lv.to_rhs(ctx);

        if(!rv.is_identifier())
        {
          printf("右辺が識別子ではない\n");
        }

      else
        if(!rhs_lv.is_reference())
        {
          printf(".%s\n",rv.get_identifier().view().data());

          printf("左辺が参照ではない\n");

          rhs_lv.print();
        }

      else
        {
          lv = value(rhs_lv.get_reference().get_property(rv.get_identifier()));
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

  else
    {
        if(lv.is_property())
        {
          auto&  p = lv.get_property();

               if(opw == gbstd::string_view(  "=")){p.set(   ri);}
          else if(opw == gbstd::string_view( "+=")){p.set(li+ri);}
          else if(opw == gbstd::string_view( "-=")){p.set(li-ri);}
          else if(opw == gbstd::string_view( "*=")){p.set(li*ri);}
          else if(opw == gbstd::string_view( "/=")){p.set(li/ri);}
          else if(opw == gbstd::string_view( "%=")){p.set(li%ri);}
          else if(opw == gbstd::string_view("<<=")){p.set(li<<ri);}
          else if(opw == gbstd::string_view(">>=")){p.set(li>>ri);}
          else if(opw == gbstd::string_view( "|=")){p.set(li|ri);}
          else if(opw == gbstd::string_view( "&=")){p.set(li&ri);}
          else if(opw == gbstd::string_view( "^=")){p.set(li^ri);}
        }

      else
        {
          auto  rhs_lv = lv.to_rhs(ctx);

            if(rhs_lv.is_reference())
            {
              auto&  objv = static_cast<value&>(rhs_lv.get_reference()());

                   if(opw == gbstd::string_view(  "=")){objv = value(   ri);}
              else if(opw == gbstd::string_view( "+=")){objv = value(li+ri);}
              else if(opw == gbstd::string_view( "-=")){objv = value(li-ri);}
              else if(opw == gbstd::string_view( "*=")){objv = value(li*ri);}
              else if(opw == gbstd::string_view( "/=")){objv = value(li/ri);}
              else if(opw == gbstd::string_view( "%=")){objv = value(li%ri);}
              else if(opw == gbstd::string_view("<<=")){objv = value(li<<ri);}
              else if(opw == gbstd::string_view(">>=")){objv = value(li>>ri);}
              else if(opw == gbstd::string_view( "|=")){objv = value(li|ri);}
              else if(opw == gbstd::string_view( "&=")){objv = value(li&ri);}
              else if(opw == gbstd::string_view( "^=")){objv = value(li^ri);}
            }

          else
            {
              printf("assignment error: 左辺が参照でもプロパティでもない\n");
            }
        }
    }
}




void
operate_stack(data_stack&  stack, const expr_element&  e, const execution_context*  ctx) noexcept
{
    if(e.is_operand())
    {
      stack.push(e.get_operand().evaluate(ctx));
    }

  else
    if(e.is_prefix_unary_operator())
    {
        if(stack.size() < 1)
        {
          printf("単項演算の演算項が足りない\n");

          return;
        }


      operate_prefix_unary(stack.top(),e.get_operator_word(),ctx);
    }

  else
    if(e.is_postfix_unary_operator())
    {
        if(stack.size() < 1)
        {
          printf("単項演算の演算項が足りない\n");

          return;
        }


      operate_postfix_unary(stack.top(),e.get_operator_word(),ctx);
    }

  else
    if(e.is_binary_operator())
    {
        if(stack.size() < 2)
        {
          printf("二項演算の演算項が足りない\n");

          return;
        }


      auto&  rv = stack.pop();
      auto&  lv = stack.top();

      operate_binary(lv,rv,e.get_operator_word(),ctx);
    }
}




}}




