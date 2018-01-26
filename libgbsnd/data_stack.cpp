#include"libgbsnd/expr.hpp"
#include"libgbsnd/script.hpp"
#include<new>


namespace gbsnd{
namespace devices{




const value&
data_stack::
operate_prefix_unary(operator_word  opw) noexcept
{
    if(opw == gbstd::string_view(""))
    {
    }


  return top();
}


const value&
data_stack::
operate_postfix_unary(operator_word  opw) noexcept
{
    if(opw == gbstd::string_view(""))
    {
    }


  return top();
}


const value&
data_stack::
operate_binary(operator_word  opw) noexcept
{
    if(opw == gbstd::string_view("+"))
    {
    }

  else
    if(opw == gbstd::string_view("-"))
    {
    }

  else
    if(opw == gbstd::string_view("*"))
    {
    }

  else
    if(opw == gbstd::string_view("/"))
    {
    }

  else
    if(opw == gbstd::string_view("%"))
    {
    }

  else
    if(opw == gbstd::string_view("<<"))
    {
    }

  else
    if(opw == gbstd::string_view(">>"))
    {
    }

  else
    if(opw == gbstd::string_view("|"))
    {
    }

  else
    if(opw == gbstd::string_view("&"))
    {
    }

  else
    if(opw == gbstd::string_view("^"))
    {
    }

  else
    if(opw == gbstd::string_view("||"))
    {
    }

  else
    if(opw == gbstd::string_view("&&"))
    {
    }

  else
    if(opw == gbstd::string_view("=="))
    {
    }

  else
    if(opw == gbstd::string_view("!="))
    {
    }

  else
    if(opw == gbstd::string_view("<"))
    {
    }

  else
    if(opw == gbstd::string_view("<="))
    {
    }

  else
    if(opw == gbstd::string_view(">"))
    {
    }

  else
    if(opw == gbstd::string_view(">="))
    {
    }

  else
    if(opw == gbstd::string_view("="))
    {
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




