#include"text_i_buffer.hpp"
#include"io_environment.hpp"
#include"text_unicode.hpp"
#include<cctype>




namespace gbstd{
namespace texts{




namespace{
bool  islower(char  c) noexcept{return((c >= 'a') && (c <= 'z'));}
bool  isupper(char  c) noexcept{return((c >= 'A') && (c <= 'Z'));}
bool  isalpha(char  c) noexcept{return(isupper(c) || islower(c));}
bool  isdigit(char  c) noexcept{return((c >= '0') && (c <= '9'));}
bool  isalnum(char  c) noexcept{return(isalpha(c) || isdigit(c));}

bool  isident0(char  c) noexcept{return(isalpha(c) || (c == '_'));}
bool  isidentn(char  c) noexcept{return(isalnum(c) || (c == '_'));}
}




void
i_buffer::
clear() noexcept
{
  delete[] m_data_source          ;
           m_data_source = nullptr;

  m_data_length = 0;
}


void
i_buffer::
reset() noexcept
{
  m_input_pointer = m_data_source;

  m_decoder = std::string_view(m_data_source,m_data_length);

  m_input_pointer[0] = 0;
}


void
i_buffer::
resize(size_t  length) noexcept
{
  clear();

  m_data_source = new char[length+1];

  m_data_length = length;

  reset();
}


namespace{
void
scan(rw_ptr<char>  dst, ro_ptr<char>&  src, size_t  n) noexcept
{
    while(n > 1)
    {
      auto  c = *src++;

        if(c == ')')
        {
          break;
        }

      else
        {
          *dst++ = c;

          --n;
        }
    }


  *dst = 0;
}
}


void
i_buffer::
push(ro_ptr<char>  s, bool  with_newline)
{
    while(*s && (m_input_pointer < m_data_tail))
    {
        if(*s == '$')
        {
          ++s;

            if(*s == '$')
            {
              *m_input_pointer++ = *s++;
            }

          else
            if(*s == '(')
            {
              char  buf[256];

              scan(buf,++s,sizeof(buf));

              push(environment::get_value(buf).data(),false);
            }

          else
            {
              *m_input_pointer++ = *s++;
            }
        }

      else
        {
          *m_input_pointer++ = *s++;
        }
    }


    if(with_newline)
    {
        if(m_input_pointer < data_tail)
        {
          *m_input_pointer++ = '\n';
        }
    }


  *m_input_pointer = 0;
}


void
i_buffer::
push(std::initializer_list<ro_ptr<char>>  ls)
{
    for(auto  s: ls)
    {
      push(s);
    }
}


char16_t
i_buffer::
pop() noexcept
{
    if(m_decoder)
    {
      return m_decoder();
    }


  return 0;
}




}}




