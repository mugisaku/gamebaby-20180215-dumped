#include"string.hpp"
#include"value.hpp"
#include<cstring>
#include<cstdio>
#include<utility>




namespace gbdn{
namespace gbdn_types{




char
string::
null;




string&
string::
operator=(const string&   rhs) noexcept
{
  clear();

  assign(rhs.m_data,rhs.m_length,rhs.m_value? new value(*rhs.m_value):nullptr);

  return *this;
}


string&
string::
operator=(string&&  rhs) noexcept
{
  clear();

  m_length = rhs.m_length;

  std::swap( m_data,rhs.m_data );
  std::swap(m_value,rhs.m_value);

  return *this;
}




void
string::
clear() noexcept
{
    if(m_data != &null)
    {
      delete[] m_data        ;
               m_data = &null;
    }


  m_length = 0;

  delete m_value          ;
         m_value = nullptr;
}


void
string::
assign(const char*  str, size_t  len, value*  v) noexcept
{
  clear();

  m_length = len;

  m_data = new char[m_length+1];

  std::memcpy(m_data,str,m_length);

  m_data[m_length] = 0;

  m_value = v;
}


void
string::
set_value(value*  v) noexcept
{
  delete m_value    ;
         m_value = v;
}


void
string::
print(int  indent) const noexcept
{
  printf("\"%s\"",m_data);

    if(m_value)
    {
      printf(":");

      m_value->print(indent);
    }
}


}}




