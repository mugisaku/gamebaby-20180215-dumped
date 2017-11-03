#include"gmbb_Script__StreamReader.hpp"
#include"gmbb_Script__List.hpp"




namespace gmbb{
namespace script{


Value
StreamReader::
read_binary_number() noexcept
{
  auto  i = read_binary_integer();

    if(*pointer == '.')
    {
      ++pointer;

      return Value(i+read_binary_fraction());
    }


  return Value(i);
}


Value
StreamReader::
read_octal_number() noexcept
{
  auto  i = read_octal_integer();

    if(*pointer == '.')
    {
      ++pointer;

      return Value(i+read_octal_fraction());
    }


  return Value(i);
}


Value
StreamReader::
read_decimal_number() noexcept
{
  auto  i = read_decimal_integer();

    if(*pointer == '.')
    {
      ++pointer;

      return Value(i+read_decimal_fraction());
    }


  return Value(i);
}


Value
StreamReader::
read_hexadecimal_number() noexcept
{
  auto  i = read_hexadecimal_integer();

    if(*pointer == '.')
    {
      ++pointer;

      return Value(i+read_hexadecimal_fraction());
    }


  return Value(i);
}




int
StreamReader::
read_binary_integer() noexcept
{
  int  i = 0;

    for(;;)
    {
      auto  c = *pointer;

        if((c == '0') ||
           (c == '1'))
        {
          i <<= 1;

            if(*pointer == '1')
            {
              i |= 1;
            }


          ++pointer;
        }

      else
        {
          break;
        }
    }


  return i;
}


double
StreamReader::
read_binary_fraction() noexcept
{
  double  d = 0.0;
  double  f = 1.0;

    for(;;)
    {
      auto  c = *pointer;

        if((c == '0') ||
           (c == '1'))
        {
          f /= 2;

            if(*pointer == '1')
            {
              d += f;
            }


          ++pointer;
        }

      else
        {
          break;
        }
    }


  return d;
}



int
StreamReader::
read_octal_integer() noexcept
{
  int  i = 0;

    while((*pointer >= '0') &&
          (*pointer <= '7'))
    {
      i <<= 3;

      i |= (*pointer++)-'0';
    }


  return i;
}


double
StreamReader::
read_octal_fraction() noexcept
{
  double  d = 0.0;
  double  f = 1.0;

    while((*pointer >= '0') &&
          (*pointer <= '7'))
    {
      d /= 8;

      d += f*((*pointer++)-'0');
    }


  return d;
}


int
StreamReader::
read_decimal_integer() noexcept
{
  int  i = 0;

    while((*pointer >= '0') &&
          (*pointer <= '9'))
    {
      i *= 10;

      i += (*pointer++)-'0';
    }


  return i;
}


double
StreamReader::
read_decimal_fraction() noexcept
{
  double  d = 0.0;
  double  f = 1.0;

    while((*pointer >= '0') &&
          (*pointer <= '9'))
    {
      f /= 10;

      d += f*((*pointer++)-'0');
    }


  return d;
}


int
StreamReader::
read_hexadecimal_integer() noexcept
{
  int  i = 0;

    for(;;)
    {
      auto  c = *pointer;

        if((c >= '0') &&
           (c <= '9'))
        {
          i <<= 4;

          i += c-'0';

          ++pointer;
        }

      else
        if(((c >= 'a') && (c <= 'f')) ||
           ((c >= 'A') && (c <= 'F')))
        {
          i <<= 4;

            switch(c)
            {
          case('a'):
          case('A'): i |= 10;break;
          case('b'):
          case('B'): i |= 11;break;
          case('c'):
          case('C'): i |= 12;break;
          case('d'):
          case('D'): i |= 13;break;
          case('e'):
          case('E'): i |= 14;break;
          case('f'):
          case('F'): i |= 15;break;
            }


          ++pointer;
        }

      else
        {
          break;
        }
    }


  return i;
}


double
StreamReader::
read_hexadecimal_fraction() noexcept
{
  double  d = 0.0;
  double  f = 1.0;

    for(;;)
    {
      auto  c = *pointer;

        if((c >= '0') &&
           (c <= '9'))
        {
          f /= 16;

          d += f*(c-'0');

          ++pointer;
        }

      else
        if(((c >= 'a') && (c <= 'f')) ||
           ((c >= 'A') && (c <= 'F')))
        {
          f /= 16;

            switch(c)
            {
          case('a'):
          case('A'): d += f*10;break;
          case('b'):
          case('B'): d += f*11;break;
          case('c'):
          case('C'): d += f*12;break;
          case('d'):
          case('D'): d += f*13;break;
          case('e'):
          case('E'): d += f*14;break;
          case('f'):
          case('F'): d += f*15;break;
            }


          ++pointer;
        }

      else
        {
          break;
        }
    }


  return d;
}


Value
StreamReader::
read_number_that_begins_by_zero() noexcept
{
  auto  c = *pointer++;

  return ((c == 'b') || (c == 'B'))? read_binary_number()
        :((c == 'o') || (c == 'O'))? read_octal_number()
        :((c == 'x') || (c == 'X'))? read_hexadecimal_number()
        :((c == '.')              )? Value(read_decimal_fraction())
        : Value(0);
}




}}




