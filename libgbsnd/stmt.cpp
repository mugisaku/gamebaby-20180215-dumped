#include"libgbsnd/stmt.hpp"
#include<new>


namespace gbsnd{
namespace devices{




void
stmt::
print() const noexcept
{
    switch(m_kind)
    {
  case(stmt_kind::expression):
      m_expr.print();
      break;
  case(stmt_kind::label     ):
      printf("label %s",m_label.data());
      break;
  case(stmt_kind::return_   ):
      printf("return ");
      m_expr.print();
      break;
  case(stmt_kind::print):
      printf("print ");
      m_expr.print();
      break;
  case(stmt_kind::sleep):
      printf("sleep ");
      m_expr.print();
      break;
  case(stmt_kind::exit):
      printf("exit ");
      m_expr.print();
      break;
  case(stmt_kind::jump_if_zero):
      printf("jump if(");
      m_expr.print();
      printf(")");
      printf(" is zero, to %s",m_label.data());
      break;
  case(stmt_kind::jump_if_not_zero):
      printf("jump if(");
      m_expr.print();
      printf(")");
      printf(" is not zero, to %s",m_label.data());
      break;
  case(stmt_kind::jump):
      printf("jump to %s",m_label.data());
      break;
    }


  printf(";");
}


}}




