#include"stream_reader.hpp"
#include<cstring>




namespace tok{
namespace tok_types{


namespace{
bool
isalpha(char  c) noexcept
{
  return(((c >= 'a') && (c <= 'z')) ||
         ((c >= 'A') && (c <= 'Z')));
}


bool
isdigit(char  c) noexcept
{
  return((c >= '0') && (c <= '9'));
}


bool
isalnum(char  c) noexcept
{
  return(isalpha(c) || isdigit(c));
}


bool
isident0(char  c) noexcept
{
  return isalpha(c) || (c == '_');
}


bool
isidentn(char  c) noexcept
{
  return isalnum(c) || (c == '_');
}
}




bool
stream_reader::
is_pointing_identifier() const noexcept
{
  return isident0(*m_pointer);
}


bool
stream_reader::
is_pointing_number() const noexcept
{
  return isdigit(*m_pointer);
}


void
stream_reader::
newline() noexcept
{
  m_line_start = m_pointer;

  ++m_line_number;
}


const std::string&
stream_reader::
read_identifier() noexcept
{
  m_string_buffer.resize(0,0);

    while(isidentn(*m_pointer))
    {
      m_string_buffer.push_back(*m_pointer++);
    }


  return m_string_buffer;
}


const std::string&
stream_reader::
read_quoted_string(char  close_char) noexcept
{
  m_string_buffer.resize(0,0);

    while(*m_pointer)
    {
      auto  c = *m_pointer++;

        if(c == close_char)
        {
          break;
        }

      else
        if(c == '\\')
        {
          break;
        }

      else
        {
          m_string_buffer.push_back(c);
        }
    }


  return m_string_buffer;
}


}}




