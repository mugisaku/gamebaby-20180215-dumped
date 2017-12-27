#include"value.hpp"
#include"list.hpp"
#include"string.hpp"
#include<cstdio>




namespace gbdn{
namespace gbdn_types{




value&
value::
operator=(value&&  rhs) noexcept
{
  clear();

  std::swap(m_kind,rhs.m_kind);

    switch(m_kind)
    {
  case(kind_type::null):
      break;
  case(kind_type::string):
      new(&m_data) string(std::move(rhs.m_data.s));
      break;
  case(kind_type::integer):
      m_data.i = rhs.m_data.i;
      break;
  case(kind_type::real):
      m_data.r = rhs.m_data.r;
      break;
  case(kind_type::list):
      new(&m_data) list(std::move(rhs.m_data.ls));
      break;
    }


  return *this;
}


value&
value::
operator=(const value&  rhs) noexcept
{
  clear();

  m_kind = rhs.m_kind;

    switch(m_kind)
    {
  case(kind_type::null):
      break;
  case(kind_type::string):
      new(&m_data) string(rhs.m_data.s);
      break;
  case(kind_type::integer):
      m_data.i = rhs.m_data.i;
      break;
  case(kind_type::real):
      m_data.r = rhs.m_data.r;
      break;
  case(kind_type::list):
      new(&m_data) list(rhs.m_data.ls);
      break;
    }


  return *this;
}




void
value::
clear() noexcept
{
    switch(m_kind)
    {
  case(kind_type::null):
      break;
  case(kind_type::string):
      m_data.s.~string();
      break;
  case(kind_type::integer):
  case(kind_type::real):
      break;
  case(kind_type::list):
      m_data.ls.~list();
      break;
    }


  m_kind = kind_type::null;
}





int            value::get_integer() const noexcept{return m_data.i;}
double            value::get_real() const noexcept{return m_data.r;}
const string&   value::get_string() const noexcept{return m_data.s;}
const list&       value::get_list() const noexcept{return m_data.ls;}




void
value::
print(int  indent) const noexcept
{
    switch(m_kind)
    {
  case(kind_type::null):
      printf("(null)");
      break;
  case(kind_type::string):
      m_data.s.print(indent);
      break;
  case(kind_type::integer):
      printf("%d",m_data.i);
      break;
  case(kind_type::real):
      printf("%f",m_data.r);
      break;
  case(kind_type::list):
      m_data.ls.print(indent);
      break;
    }
}




}}




