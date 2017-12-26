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


bool
ispunct(char  c) noexcept
{
  return((c == '!') ||
         (c == '?') ||
         (c == '+') ||
         (c == '-') ||
         (c == '*') ||
         (c == '/') ||
         (c == '%') ||
         (c == '|') ||
         (c == '&') ||
         (c == '=') ||
         (c == '<') ||
         (c == '>') ||
         (c == '(') ||
         (c == ')') ||
         (c == '{') ||
         (c == '}') ||
         (c == '[') ||
         (c == ']') ||
         (c == ':') ||
         (c == ';') ||
         (c == ',') ||
         (c == '.') ||
         (c == '~') ||
         (c == '^') ||
         (c == '#'));
}
}




void
stream_reader::
newline() noexcept
{
  m_line_start = m_pointer;

  ++m_line_number;
}


identifier
stream_reader::
read_identifier() noexcept
{
  std::string  s;

    while(isidentn(*m_pointer))
    {
      s.push_back(*m_pointer++);
    }


  return identifier(std::move(s));
}


punctuation_string
stream_reader::
read_punctuation_string() noexcept
{
  std::string  s;

    while(ispunct(*m_pointer))
    {
      s.push_back(*m_pointer++);
    }


  return punctuation_string(std::move(s));
}


quoted_string
stream_reader::
read_quoted_string(char  close_char) noexcept
{
  std::string  s;

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
          s.push_back(c);
        }
    }


  return quoted_string(std::move(s));
}


token
stream_reader::
read_token()
{
  auto  first_c = *m_pointer;

  token_info ti(m_line_start,m_pointer,m_line_number);

    if((first_c == '\"') ||
       (first_c == '\''))
    {
      ++m_pointer;

      return token(ti,read_quoted_string(first_c));
    }

  else
    if(isident0(first_c))
    {
      return token(ti,read_identifier());
    }

  else
    if(first_c == '0')
    {
      ++m_pointer;

      return token(ti,read_number_that_begins_by_zero());
    }

  else
    if((first_c >= '1') &&
       (first_c <= '9'))
    {
      return token(ti,read_decimal_number());
    }

  else
    if((first_c >= '1') &&
       (first_c <= '9'))
    {
      return token(ti,read_decimal_number());
    }

  else
    if(ispunct(first_c))
    {
      return token(ti,read_punctuation_string());
    }

  else
    {
      printf("%c(%d)は処理できない ",first_c,first_c);
    }


  throw ti;
}


}}




