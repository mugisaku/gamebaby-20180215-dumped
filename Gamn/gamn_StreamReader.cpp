#include"gamn_StreamReader.hpp"
#include"gamn_List.hpp"




namespace gamn{


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
bool
isident0(char  c)
{
  return isalpha(c) || (c == '_');
}


bool
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




List*
StreamReader::
read_list(covered_ptr<List>  parent, char  opening, char  closing)
{
  ++pointer;

  return new List(*this,parent,opening,closing);
}


Value
StreamReader::
read_value(covered_ptr<List>  parent)
{
  auto  first_c = *pointer;

    if(first_c)
    {
      bool  neg = false;

        if(first_c == '-')
        {
          ++pointer;

          first_c = *pointer;

          neg = true;
        }


           if(first_c == '{'){return Value(read_list(parent,first_c,'}'));}
      else if(first_c == '('){return Value(read_list(parent,first_c,')'));}
      else if(first_c == '['){return Value(read_list(parent,first_c,']'));}
      else
        if(first_c == '\"')
        {
          ++pointer;

          auto  s = read_string();

          skip_spaces();

            if(*pointer == ':')
            {
              ++pointer;

              skip_spaces();


              auto  v = read_value(parent);

                if(v.get_name().size())
                {
                  v = Value(new Value(std::move(v)));
                }


              v.set_name(std::move(s));

              return std::move(v);
            }

          else
            {
              return Value(std::move(s));
            }
        }

      else
        if(isident0(first_c))
        {
          auto  s = read_identifier();

          skip_spaces();

            if(*pointer == ':')
            {
              ++pointer;

              skip_spaces();


              auto  v = read_value(parent);

                if(v.get_name().size())
                {
                  v = Value(new Value(std::move(v)));
                }


              v.set_name(std::move(s));

              return std::move(v);
            }

          else
            {
              return Value(std::move(s));
            }
        }

      else
        if(first_c == '0')
        {
          ++pointer;

          auto  v = read_number_that_begins_by_zero();

          return Value(neg? v.neg():v);
        }

      else
        if((first_c >= '1') &&
           (first_c <= '9'))
        {
          auto  v = read_decimal_number();

          return Value(neg? v.neg():v);
        }

      else
        {
          throw StreamError(*this,"%cは処理できない ",first_c);
        }
    }


  return Value();
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


}




