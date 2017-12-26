#include"token.hpp"




namespace tok{
namespace tok_types{


void
token::
clear() noexcept
{
    switch(m_kind)
    {
  case(kind::identifier):
  case(kind::quoted_string):
  case(kind::punctuation_string):
      m_data.s.~basic_string();
      break;
    }


  m_kind = kind::null;
}


token&
token::
operator=(const token&   rhs) noexcept
{
    if(this != &rhs)
    {
      clear();

      m_kind = rhs.m_kind;
      m_info = rhs.m_info;

        switch(m_kind)
        {
      case(kind::integer):
          m_data.i = rhs.m_data.i;
          break;
      case(kind::identifier):
      case(kind::quoted_string):
      case(kind::punctuation_string):
          new(&m_data) std::string(rhs.m_data.s);
          break;
        }
    }


  return *this;
}


token&
token::
operator=(token&&  rhs) noexcept
{
    if(this != &rhs)
    {
      clear();

      std::swap(m_kind,rhs.m_kind);

      m_info = rhs.m_info;

        switch(m_kind)
        {
      case(kind::integer):
          m_data.i = rhs.m_data.i;
          break;
      case(kind::identifier):
      case(kind::quoted_string):
      case(kind::punctuation_string):
          new(&m_data) std::string(std::move(rhs.m_data.s));
          break;
        }
    }


  return *this;
}


void
token::
print() const noexcept
{
    switch(m_kind)
    {
  case(kind::integer):
      printf("%u ",m_data.i);
      break;
  case(kind::identifier):
  case(kind::punctuation_string):
      printf("%s ",m_data.s.data());
      break;
  case(kind::quoted_string):
      printf("\"%s \"",m_data.s.data());
      break;
    }
}




}}




