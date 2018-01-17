#include"libgbsnd/script.hpp"
#include<new>


namespace gbsnd{
namespace devices{




script_token&
script_token::
operator=(uint64_t  i) noexcept
{
  clear();

  m_kind = kind::integer_literal;

  m_data.i = i;

  return *this;
}


script_token&
script_token::
operator=(gbstd::string&&  id) noexcept
{
  clear();

  m_kind = kind::identifier;

  new(&m_data) gbstd::string(std::move(id));

  return *this;
}


script_token&
script_token::
operator=(const operator_code&  opco) noexcept
{
  clear();

  m_kind = kind::operator_code;

  m_data.opco = opco;

  return *this;
}


script_token&
script_token::
operator=(script_token_string&&  toks) noexcept
{
  clear();

  m_kind = kind::token_string;

  new(&m_data) script_token_string(std::move(toks));

  return *this;
}


script_token&
script_token::
operator=(const script_token&  rhs) noexcept
{
  clear();

  m_kind = rhs.m_kind;

    switch(m_kind)
    {
  case(kind::integer_literal):
      m_data.i = rhs.m_data.i;
      break;
  case(kind::identifier):
      new(&m_data) gbstd::string(rhs.m_data.id);
      break;
  case(kind::operator_code):
      m_data.opco = rhs.m_data.opco;
      break;
  case(kind::token_string):
      new(&m_data) script_token_string(rhs.m_data.toks);
      break;
    }


  return *this;
}


script_token&
script_token::
operator=(script_token&&  rhs) noexcept
{
  clear();

  std::swap(m_kind,rhs.m_kind);

    switch(m_kind)
    {
  case(kind::integer_literal):
      m_data.i = rhs.m_data.i;
      break;
  case(kind::identifier):
      new(&m_data) gbstd::string(std::move(rhs.m_data.id));
      break;
  case(kind::operator_code):
      m_data.opco = rhs.m_data.opco;
      break;
  case(kind::token_string):
      new(&m_data) script_token_string(std::move(rhs.m_data.toks));
      break;
    }


  return *this;
}



void
script_token::
clear() noexcept
{
    switch(m_kind)
    {
  case(kind::integer_literal):
      break;
  case(kind::identifier):
      gbstd::destruct(m_data.id);
      break;
  case(kind::operator_code):
      break;
  case(kind::token_string):
      gbstd::destruct(m_data.toks);
      break;
    }


  m_kind = kind::null;
}


void
script_token::
print(FILE*  f, int  indent) const noexcept
{
    switch(m_kind)
    {
  case(kind::integer_literal):
      fprintf(f,"%lu",m_data.i);
      break;
  case(kind::identifier):
      fprintf(f,"%s ",m_data.id.data());
      break;
  case(kind::operator_code):
      fprintf(f,"%s ",m_data.opco.get_string());
      break;
  case(kind::token_string):
      m_data.toks.print(f,indent);
      break;
    }
}


}}




