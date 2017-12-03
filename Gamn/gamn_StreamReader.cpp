#include"gamn_StreamReader.hpp"
#include"gamn_List.hpp"
#include<cstring>




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


String
StreamReader::
read_identifier() noexcept
{
  String  s;

  clear_buffer();

    while(isidentn(*pointer))
    {
      push(*pointer++);
    }


  s.assign(buffer,length);

  return std::move(s);
}


String
StreamReader::
read_string() noexcept
{
  String  s;

  clear_buffer();

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
          push(c);
        }
    }


  s.assign(buffer,length);

  return std::move(s);
}


void
StreamReader::
push(char  c) noexcept
{
    if(length >= allocated_length)
    {
      auto  new_buffer = new char[allocated_length*2];

      std::memcpy(new_buffer,buffer,allocated_length);

      delete[] buffer             ;
               buffer = new_buffer;

      allocated_length *= 2;
    }


  buffer[length++] = c;
}


void
StreamReader::
allocate_initial_buffer() noexcept
{
  constexpr size_t  initial_allocation_size = 1024;

  buffer = new char[initial_allocation_size];

  allocated_length = initial_allocation_size;
}


void
StreamReader::
clear_buffer() noexcept
{
  length = 0;
}


Value
StreamReader::
read_value()
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


        if(first_c == '{')
        {
          ++pointer;

          return Value(new List(*this,'}'));
        }

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

              s.set_value(new Value(read_value()));
            }


          return Value(std::move(s));
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

              s.set_value(new Value(read_value()));
            }


          return Value(std::move(s));
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
          throw StreamError(*this,"%c(%d)は処理できない ",first_c,first_c);
        }
    }


  return Value();
}


}




