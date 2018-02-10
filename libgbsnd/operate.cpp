#include"libgbsnd/expr.hpp"
#include"libgbsnd/script.hpp"
#include<new>


namespace gbsnd{
namespace devices{




void
operate_prefix_unary(operand&  o, operator_word  opw, const execution_context*  ctx) noexcept
{
  auto  i = o.evaluate(ctx).get_integer_safely();

    if(opw == gbstd::string_view("!"))
    {
      o = operand(value(!i));
    }

  else
    if(opw == gbstd::string_view("~"))
    {
      o = operand(value(~i));
    }

  else
    if(opw == gbstd::string_view("-"))
    {
      o = operand(value(-i));
    }
}


void
operate_postfix_unary(operand&  o, operator_word  opw, const execution_context*  ctx) noexcept
{
    if(opw == gbstd::string_view(""))
    {
    }
}


void
operate_binary(operand&  lo, operand&  ro, operator_word  opw, const execution_context*  ctx) noexcept
{
  auto  lv = lo.evaluate(ctx);

    if(opw == gbstd::string_view("||"))
    {
        if(lv.get_integer_safely())
        {
          lo = operand(value(true));
        }

      else
        {
          lo = operand(value(ro.evaluate(ctx).get_integer_safely()));
        }


      return;
    }

  else
    if(opw == gbstd::string_view("&&"))
    {
        if(lv.get_integer_safely())
        {
          lo = operand(value(ro.evaluate(ctx).get_integer_safely()));
        }

      else
        {
          lo = operand(value(false));
        }


      return;
    }



    if(opw == gbstd::string_view("."))
    {
        if(!ro.is_identifier())
        {
          printf("右辺が識別子ではない\n");
        }

      else
        if(!lv.is_reference())
        {
          printf(".%s\n",ro.get_identifier().view().data());

          printf("左辺が参照ではない\n");

          lv.print();
        }

      else
        {
          lo = operand(value(lv.get_reference().get_property(ro.get_identifier())));
        }


      return;
    }

  else
    if(opw == gbstd::string_view("->"))
    {
      return;
    }



  auto  ri = ro.evaluate(ctx).get_integer_safely();
  auto  li =               lv.get_integer_safely();

    if((opw == gbstd::string_view(  "=")) ||
       (opw == gbstd::string_view( "+=")) ||
       (opw == gbstd::string_view( "-=")) ||
       (opw == gbstd::string_view( "*=")) ||
       (opw == gbstd::string_view( "/=")) ||
       (opw == gbstd::string_view( "%=")) ||
       (opw == gbstd::string_view("<<=")) ||
       (opw == gbstd::string_view(">>=")) ||
       (opw == gbstd::string_view( "|=")) ||
       (opw == gbstd::string_view( "&=")) ||
       (opw == gbstd::string_view( "^=")))
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
          else {printf("プロパティーに対する不正な演算 %s\n",short_string(opw).data());}
        }

      else
        if(lv.is_reference())
        {
          auto&  objv = static_cast<value&>(lv.get_reference()());

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
          else {printf("参照に対する不正な演算\n");}
        }


      return;
    }




       if(opw == gbstd::string_view("+")){lo = operand(value(li+ri));}
  else if(opw == gbstd::string_view("-")){lo = operand(value(li-ri));}
  else if(opw == gbstd::string_view("*")){lo = operand(value(li*ri));}
  else
    if(opw == gbstd::string_view("/"))
    {
        if(!ri)
        {
          printf("div error: ゼロ除算\n");
        }

      else
        {
          lo = operand(value(li/ri));
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
          lo = operand(value(li%ri));
        }
    }

  else if(opw == gbstd::string_view("<<")){lo = operand(value(li<<ri));}
  else if(opw == gbstd::string_view(">>")){lo = operand(value(li>>ri));}
  else if(opw == gbstd::string_view("|")) {lo = operand(value(li|ri));}
  else if(opw == gbstd::string_view("&")) {lo = operand(value(li&ri));}
  else if(opw == gbstd::string_view("^")) {lo = operand(value(li^ri));}
  else if(opw == gbstd::string_view("==")){lo = operand(value(li == ri));}
  else if(opw == gbstd::string_view("!=")){lo = operand(value(li != ri));}
  else if(opw == gbstd::string_view("<")) {lo = operand(value(li <  ri));}
  else if(opw == gbstd::string_view("<=")){lo = operand(value(li <= ri));}
  else if(opw == gbstd::string_view(">")) {lo = operand(value(li >  ri));}
  else if(opw == gbstd::string_view(">=")){lo = operand(value(li >= ri));}
  else
    if(opw == gbstd::string_view("::"))
    {
    }

  else
    if(opw == gbstd::string_view("()"))
    {
    }

  else
    if(opw == gbstd::string_view(","))
    {
    }
}




void
operate_stack(data_stack&  stack, const expr_element&  e, const execution_context*  ctx) noexcept
{
    if(e.is_operand())
    {
      stack.push(e.get_operand());
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


      auto&  ro = stack.pop();
      auto&  lo = stack.top();

      operate_binary(lo,ro,e.get_operator_word(),ctx);
    }
}




}}




