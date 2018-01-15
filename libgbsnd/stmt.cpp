#include"libgbsnd/stmt.hpp"
#include<new>


namespace gbsnd{
namespace devices{




stmt&
stmt::
operator=(expr&&  e) noexcept
{
  clear();

  m_kind = kind::expression;

  new(&m_data) expr(std::move(e));

  return *this;
}


stmt&
stmt::
operator=(block&&  blk) noexcept
{
  clear();

  m_kind = kind::block;

  new(&m_data) block(std::move(blk));

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
operator=(break_stmt  brk) noexcept
{
  clear();

  m_kind = kind::break_;

  return *this;
}


stmt&
stmt::
operator=(continue_stmt  cnt) noexcept
{
  clear();

  m_kind = kind::continue_;

  return *this;
}


stmt&
stmt::
operator=(default_stmt  dfl) noexcept
{
  clear();

  m_kind = kind::default_;

  return *this;
}


stmt&
stmt::
operator=(case_stmt  cas) noexcept
{
  clear();

  m_kind = kind::case_;

  new(&m_data) case_stmt(cas);

  return *this;
}


stmt&
stmt::
operator=(const stmt&  rhs) noexcept
{
  clear();

  m_kind = rhs.m_kind;

    switch(m_kind)
    {
  case(kind::expression): new(&m_data) expr(rhs.m_data.e);break;
  case(kind::label     ): new(&m_data) label_stmt(rhs.m_data.lbl);break;
  case(kind::block     ): new(&m_data) block(rhs.m_data.blk);break;
  case(kind::if_       ): break;
  case(kind::while_    ): break;
  case(kind::for_      ): break;
  case(kind::break_    ): break;
  case(kind::continue_ ): break;
  case(kind::goto_     ): break;
  case(kind::switch_   ): break;
  case(kind::case_     ): new(&m_data) case_stmt(rhs.m_data.cas);break;
  case(kind::default_  ): break;
  case(kind::return_   ): new(&m_data) return_stmt(rhs.m_data.ret);break;
    }


  return *this;
}


stmt&
stmt::
operator=(stmt&&  rhs) noexcept
{
  clear();

  std::swap(m_kind,rhs.m_kind);

    switch(m_kind)
    {
  case(kind::expression): new(&m_data) expr(std::move(rhs.m_data.e));break;
  case(kind::label     ): new(&m_data) label_stmt(std::move(rhs.m_data.lbl));break;
  case(kind::block     ): new(&m_data) block(std::move(rhs.m_data.blk));break;
  case(kind::if_       ): break;
  case(kind::while_    ): break;
  case(kind::for_      ): break;
  case(kind::break_    ): break;
  case(kind::continue_ ): break;
  case(kind::goto_     ): break;
  case(kind::switch_   ): break;
  case(kind::case_     ): new(&m_data) case_stmt(std::move(rhs.m_data.cas));break;
  case(kind::default_  ): break;
  case(kind::return_   ): new(&m_data) return_stmt(std::move(rhs.m_data.ret));break;
    }


  return *this;
}



void
stmt::
clear() noexcept
{
    switch(m_kind)
    {
  case(kind::expression): m_data.e.~expr();break;
  case(kind::label     ): m_data.lbl.~label_stmt();break;
  case(kind::block     ): m_data.blk.~block();break;
  case(kind::if_       ): break;
  case(kind::while_    ): break;
  case(kind::for_      ): break;
  case(kind::break_    ): break;
  case(kind::continue_ ): break;
  case(kind::goto_     ): break;
  case(kind::switch_   ): break;
  case(kind::case_     ): break;
  case(kind::default_  ): break;
  case(kind::return_   ): m_data.ret.~return_stmt();break;
    }


  m_kind = kind::null;
}


}}




