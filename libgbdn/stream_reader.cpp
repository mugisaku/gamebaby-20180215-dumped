#include"stream_reader.hpp"
#include"list.hpp"
#include<cstring>




namespace gbdn{


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




string
stream_reader::
read_identifier() noexcept
{
  string  s;

  clear_buffer();

    while(isidentn(*pointer))
    {
      push(*pointer++);
    }


  s.assign(buffer,length);

  return std::move(s);
}


string
stream_reader::
read_string(char  close_char) noexcept
{
  string  s;

  clear_buffer();

    while(*pointer)
    {
      auto  c = *pointer++;

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
          push(c);
        }
    }


  s.assign(buffer,length);

  return std::move(s);
}


void
stream_reader::
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
stream_reader::
allocate_initial_buffer() noexcept
{
  constexpr size_t  initial_allocation_size = 512;

  buffer = new char[initial_allocation_size];

  allocated_length = initial_allocation_size;
}


void
stream_reader::
clear_buffer() noexcept
{
  length = 0;
}


value
stream_reader::
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

          return value(new list(*this,'}'));
        }

      else
        if((first_c == '\"') ||
           (first_c == '\''))
        {
          ++pointer;

          auto  s = read_string(first_c);

          skip_spaces();

            if(*pointer == ':')
            {
              ++pointer;

              skip_spaces();

              s.set_value(new value(read_value()));
            }


          return value(std::move(s));
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

              s.set_value(new value(read_value()));
            }


          return value(std::move(s));
        }

      else
        if(first_c == '0')
        {
          ++pointer;

          auto  v = read_number_that_begins_by_zero();

          return value(neg? -v.get_integer():v.get_integer());
        }

      else
        if((first_c >= '1') &&
           (first_c <= '9'))
        {
          auto  v = read_decimal_number();

          return value(neg? -v.get_integer():v.get_integer());
        }

      else
        {
          throw stream_error(*this,"%c(%d)は処理できない ",first_c,first_c);
        }
    }


  return value();
}


}




