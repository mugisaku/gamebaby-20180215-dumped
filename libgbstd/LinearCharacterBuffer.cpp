#include"gmbb_LinearCharacterBuffer.hpp"
#include"gmbb_environment.hpp"
#include"gmbb_unicode.hpp"
#include<cctype>




namespace gmbb{




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
LinearCharacterBuffer::
clear() noexcept
{
  delete[] data_source          ;
           data_source = nullptr;

  data_length = 0;
}


void
LinearCharacterBuffer::
reset() noexcept
{
   input_pointer = data_source;
  output_pointer = data_source;

  input_pointer[0] = 0;
}


void
LinearCharacterBuffer::
resize(size_t  length) noexcept
{
  clear();

  data_source = new char[length+1];

  data_length = length;

  data_tail = data_source+data_length;

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
LinearCharacterBuffer::
push(ro_ptr<char>  s, bool  with_newline)
{
    while(*s && (input_pointer < data_tail))
    {
        if(*s == '$')
        {
          ++s;

            if(*s == '$')
            {
              *input_pointer++ = *s++;
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
              *input_pointer++ = *s++;
            }
        }

      else
        {
          *input_pointer++ = *s++;
        }
    }


    if(with_newline)
    {
        if(input_pointer < data_tail)
        {
          *input_pointer++ = '\n';
        }
    }


  *input_pointer = 0;
}


void
LinearCharacterBuffer::
push(std::initializer_list<ro_ptr<char>>  ls)
{
    for(auto  s: ls)
    {
      push(s);
    }
}


char16_t
LinearCharacterBuffer::
pop() noexcept
{
    if(*output_pointer)
    {
      auto  byte_number = utf8_byte_number(*output_pointer);

        if((output_pointer+static_cast<int>(byte_number)) <= data_tail)
        {
          auto  c = to_char32(output_pointer,byte_number);

          output_pointer += byte_number;

          return c;
        }
    }


  return 0;
}




}




