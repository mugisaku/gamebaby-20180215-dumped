#include"libgbsnd/expr.hpp"
#include"libgbsnd/script.hpp"
#include<new>


namespace gbsnd{
namespace devices{




const value&
data_stack::
operate_prefix_unary(operator_word  opw, const execution_context*  ctx) noexcept
{
  auto  i = top().to_rhs(ctx).get_integer_safely();

    if(opw == gbstd::string_view("!"))
    {
      top() = value(!i);
    }

  else
    if(opw == gbstd::string_view("~"))
    {
      top() = value(~i);
    }

  else
    if(opw == gbstd::string_view("-"))
    {
      top() = value(-i);
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
  auto  rv = pop();
  auto  lv = top();

    if(opw == gbstd::string_view("||"))
    {
        if(lv.to_rhs(ctx).get_integer_safely())
        {
          top() = value(true);
        }

      else
        {
          top() = value(rv.to_rhs(ctx).get_integer_safely());
        }


      return top();
    }

  else
    if(opw == gbstd::string_view("&&"))
    {
        if(lv.to_rhs(ctx).get_integer_safely())
        {
          top() = value(rv.to_rhs(ctx).get_integer_safely());
        }

      else
        {
          top() = value(false);
        }


      return top();
    }




  auto  ri = rv.to_rhs(ctx).get_integer_safely();
  auto  li = lv.to_rhs(ctx).get_integer_safely();

       if(opw == gbstd::string_view("+")){top() = value(li+ri);}
  else if(opw == gbstd::string_view("-")){top() = value(li-ri);}
  else if(opw == gbstd::string_view("*")){top() = value(li*ri);}
  else
    if(opw == gbstd::string_view("/"))
    {
        if(!ri)
        {
          printf("div error: ゼロ除算\n");
        }

      else
        {
          top() = value(li/ri);
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
          top() = value(li%ri);
        }
    }

  else if(opw == gbstd::string_view("<<")){top() = value(li<<ri);}
  else if(opw == gbstd::string_view(">>")){top() = value(li>>ri);}
  else if(opw == gbstd::string_view("|")) {top() = value(li|ri);}
  else if(opw == gbstd::string_view("&")) {top() = value(li&ri);}
  else if(opw == gbstd::string_view("^")) {top() = value(li^ri);}
  else if(opw == gbstd::string_view("==")){top() = value(li == ri);}
  else if(opw == gbstd::string_view("!=")){top() = value(li != ri);}
  else if(opw == gbstd::string_view("<")) {top() = value(li <  ri);}
  else if(opw == gbstd::string_view("<=")){top() = value(li <= ri);}
  else if(opw == gbstd::string_view(">")) {top() = value(li >  ri);}
  else if(opw == gbstd::string_view(">=")){top() = value(li >= ri);}
  else
    if(opw == gbstd::string_view("::"))
    {
    }

  else
    if(opw == gbstd::string_view("."))
    {
      lv = lv.to_rhs(ctx);

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
          lv = lv.to_rhs(ctx);

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
            }

          else
            {
              printf("assignment error: 左辺が参照でもプロパティでもない\n");
            }
        }
    }


  return top();
}




}}




