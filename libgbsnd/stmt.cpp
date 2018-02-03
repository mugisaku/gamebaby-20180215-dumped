#include"libgbsnd/stmt.hpp"
#include<new>


namespace gbsnd{
namespace devices{




stmt&
stmt::
operator=(expr_array&&  e) noexcept
{
  clear();

  m_kind = kind::expression;

  new(&m_data) expr_array(std::move(e));

  return *this;
}


stmt&
stmt::
operator=(label_stmt&&  lbl) noexcept
{
  clear();

  m_kind = kind::label;

  new(&m_data) label_stmt(std::move(lbl));

  return *this;
}


stmt&
stmt::
operator=(return_stmt&&  ret) noexcept
{
  clear();

  m_kind = kind::return_;

  new(&m_data) return_stmt(std::move(ret));

  return *this;
}


stmt&
stmt::
operator=(sleep_stmt&&  slp) noexcept
{
  clear();

  m_kind = kind::sleep;

  new(&m_data) sleep_stmt(std::move(slp));

  return *this;
}


stmt&
stmt::
operator=(print_stmt&&  prn) noexcept
{
  clear();

  m_kind = kind::print;

  new(&m_data) print_stmt(std::move(prn));

  return *this;
}


stmt&
stmt::
operator=(exit_stmt&&  exi) noexcept
{
  clear();

  m_kind = kind::exit;

  new(&m_data) exit_stmt(std::move(exi));

  return *this;
}


stmt&
stmt::
operator=(branch_stmt&&  bra) noexcept
{
  clear();

  m_kind = kind::branch;

  new(&m_data) branch_stmt(std::move(bra));

  return *this;
}


stmt&
stmt::
operator=(jump_stmt&&  jmp) noexcept
{
  clear();

  m_kind = kind::jump;

  new(&m_data) jump_stmt(std::move(jmp));

  return *this;
}


stmt&
stmt::
operator=(const stmt&  rhs) noexcept
{
    if(this != &rhs)
    {
      clear();

      m_kind = rhs.m_kind;

        switch(m_kind)
        {
      case(kind::expression): new(&m_data) expr_array(rhs.m_data.e);break;
      case(kind::label     ): new(&m_data) label_stmt(rhs.m_data.lbl);break;
      case(kind::return_   ): new(&m_data) return_stmt(rhs.m_data.ret);break;
      case(kind::sleep     ): new(&m_data) sleep_stmt(rhs.m_data.slp);break;
      case(kind::print     ): new(&m_data) print_stmt(rhs.m_data.prn);break;
      case(kind::exit      ): new(&m_data) exit_stmt(rhs.m_data.exi);break;
      case(kind::branch    ): new(&m_data) branch_stmt(rhs.m_data.bra);break;
      case(kind::jump      ): new(&m_data) jump_stmt(rhs.m_data.jmp);break;
        }
    }


  return *this;
}


stmt&
stmt::
operator=(stmt&&  rhs) noexcept
{
    if(this != &rhs)
    {
      clear();

      std::swap(m_kind,rhs.m_kind);

        switch(m_kind)
        {
      case(kind::expression): new(&m_data) expr_array(std::move(rhs.m_data.e));break;
      case(kind::label     ): new(&m_data) label_stmt(std::move(rhs.m_data.lbl));break;
      case(kind::return_   ): new(&m_data) return_stmt(std::move(rhs.m_data.ret));break;
      case(kind::sleep     ): new(&m_data) sleep_stmt(std::move(rhs.m_data.slp));break;
      case(kind::print     ): new(&m_data) print_stmt(std::move(rhs.m_data.prn));break;
      case(kind::exit      ): new(&m_data) exit_stmt(std::move(rhs.m_data.exi));break;
      case(kind::branch    ): new(&m_data) branch_stmt(std::move(rhs.m_data.bra));break;
      case(kind::jump      ): new(&m_data) jump_stmt(rhs.m_data.jmp);break;
        }
    }


  return *this;
}



void
stmt::
clear() noexcept
{
    switch(m_kind)
    {
  case(kind::expression): gbstd::destruct(m_data.e);break;
  case(kind::label     ): gbstd::destruct(m_data.lbl);break;
  case(kind::return_   ): gbstd::destruct(m_data.ret);break;
  case(kind::sleep     ): gbstd::destruct(m_data.slp);break;
  case(kind::print     ): gbstd::destruct(m_data.prn);break;
  case(kind::exit      ): gbstd::destruct(m_data.exi);break;
  case(kind::branch    ): gbstd::destruct(m_data.bra);break;
  case(kind::jump      ): gbstd::destruct(m_data.jmp);break;
    }


  m_kind = kind::null;
}


void
stmt::
print() const noexcept
{
    switch(m_kind)
    {
  case(kind::expression): m_data.e.print();break;
  case(kind::label     ):
      printf("label %s",m_data.lbl.get_text().data());
      break;
  case(kind::return_   ):
      printf("return ");
      m_data.ret.get_expr().print();
      break;
  case(kind::print):
      printf("print ");
      m_data.prn.get_expr().print();
      break;
  case(kind::sleep):
      printf("sleep ");
      m_data.slp.get_expr().print();
      break;
  case(kind::exit):
      printf("exit ");
      m_data.slp.get_expr().print();
      break;
  case(kind::branch):
      printf("branch(");
      m_data.bra.get_expr().print();
      printf(")");
      printf(" if %s, goto %s",m_data.bra.get_boolean()? "true":"false",m_data.bra.get_dst_label().data());
      break;
  case(kind::jump):
      printf("jump to %s",m_data.jmp.get_dst_label().data());
      break;
    }


  printf(";");
}


}}




