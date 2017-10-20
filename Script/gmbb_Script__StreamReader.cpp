#include"gmbb_Script__StreamReader.hpp"




namespace gmbb{
namespace script{


void
StreamReader::
skip_spaces() noexcept
{
    for(;;)
    {
      auto  c = *pointer;

        if((c ==  ' ') ||
           (c == '\t') ||
           (c == '\r') ||
           (c == '\v'))
        {
          ++pointer;
        }

      else           
        if(c == '\n')
        {
          ++pointer;

          newline();
        }

      else
        {
          break;
        }           
    }
}




namespace{
constexpr bool
isident0(char  c)
{
  return isalpha(c) || (c == '_');
}


constexpr bool
isidentn(char  c)
{
  return isalnum(c) || (c == '_');
}
}


std::string
StreamReader::
read_identifier() noexcept
{
  std::string  s;

    while(isidentn(*pointer))
    {
      s += *pointer++;
    }


  return std::move(s);
}


std::string
StreamReader::
read_string() noexcept
{
  std::string  s;

    while(*pointer)
    {
      auto  c = *pointer++;

        if(c == '\"')
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
          s += c;
        }
    }


  return std::move(s);
}


int
StreamReader::
read_decimal_integer() noexcept
{
  int  i = 0;

    while((*pointer >= '1') &&
          (*pointer <= '9'))
    {
      i *= 10;

      i += (*pointer++)-'0';
    }


  return i;
}


int
StreamReader::
read_integer_that_begins_by_zero() noexcept
{
  auto  c = *pointer;

  return ((c == 'b') || (c == 'B'))? 0
        :((c == 'o') || (c == 'O'))? 0
        :((c == 'x') || (c == 'X'))? 0
        :0;
}


TokenString*
StreamReader::
read_token_string(covered_ptr<TokenString>  parent, char  opening, char  closing)
{
  ++pointer;

  return new TokenString(*this,parent,opening,closing);
}


Token
StreamReader::
operator()(covered_ptr<TokenString>  parent)
{
  auto  first_c = *pointer;

    if(first_c)
    {
           if(first_c == '{'){return Token(read_token_string(parent,first_c,'}'));}
      else if(first_c == '('){return Token(read_token_string(parent,first_c,')'));}
      else if(first_c == '['){return Token(read_token_string(parent,first_c,']'));}
      else
        if(first_c == '\"')
        {
          ++pointer;

          return Token(read_string());
        }

      else
        if(first_c == '\'')
        {
        }

      else
        if(isident0(first_c))
        {
          return Token(Identifier(read_identifier()));
        }

      else
        if(first_c == '0')
        {
          ++pointer;

          return Token(read_integer_that_begins_by_zero());
        }

      else
        if((first_c >= '1') &&
           (first_c <= '9'))
        {
          return Token(read_decimal_integer());
        }

      else
        {
          throw StreamError(*this,"%cは処理できない ",first_c);
        }
    }


  return Token();
}




std::string
make_string_from_file(const char*  filepath)
{
  FileStream  fs(filepath);

    if(fs)
    {
      std::string  s;

        for(;;)
        {
          auto  c = fs.getc();

            if(fs.eof() || fs.error())
            {
              break;
            }


          s += c;
        }


      return std::move(s);
    }

  else
    {
      throw StreamError(StreamContext(),"%sがみつからない",filepath);
    }
}


}}




