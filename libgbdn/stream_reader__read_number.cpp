#include"stream_reader.hpp"
#include"list.hpp"




namespace gbdn{


value
stream_reader::
read_binary_number() noexcept
{
  auto  i = read_binary_integer();

    if(*m_pointer == '.')
    {
      ++m_pointer;

      return value(i+read_binary_fraction());
    }


  return value(i);
}


value
stream_reader::
read_octal_number() noexcept
{
  auto  i = read_octal_integer();

    if(*m_pointer == '.')
    {
      ++m_pointer;

      return value(i+read_octal_fraction());
    }


  return value(i);
}


value
stream_reader::
read_decimal_number() noexcept
{
  auto  i = read_decimal_integer();

    if(*m_pointer == '.')
    {
      ++m_pointer;

      return value(i+read_decimal_fraction());
    }


  return value(i);
}


value
stream_reader::
read_hexadecimal_number() noexcept
{
  auto  i = read_hexadecimal_integer();

    if(*m_pointer == '.')
    {
      ++m_pointer;

      return value(i+read_hexadecimal_fraction());
    }


  return value(i);
}




int
stream_reader::
read_binary_integer() noexcept
{
  int  i = 0;

    for(;;)
    {
      auto  c = *m_pointer;

        if((c == '0') ||
           (c == '1'))
        {
          i <<= 1;

            if(*m_pointer == '1')
            {
              i |= 1;
            }


          ++m_pointer;
        }

      else
        {
          break;
        }
    }


  return i;
}


double
stream_reader::
read_binary_fraction() noexcept
{
  double  d = 0.0;
  double  f = 1.0;

    for(;;)
    {
      auto  c = *m_pointer;

        if((c == '0') ||
           (c == '1'))
        {
          f /= 2;

            if(*m_pointer == '1')
            {
              d += f;
            }


          ++m_pointer;
        }

      else
        {
          break;
        }
    }


  return d;
}



int
stream_reader::
read_octal_integer() noexcept
{
  int  i = 0;

    while((*m_pointer >= '0') &&
          (*m_pointer <= '7'))
    {
      i <<= 3;

      i |= (*m_pointer++)-'0';
    }


  return i;
}


double
stream_reader::
read_octal_fraction() noexcept
{
  double  d = 0.0;
  double  f = 1.0;

    while((*m_pointer >= '0') &&
          (*m_pointer <= '7'))
    {
      d /= 8;

      d += f*((*m_pointer++)-'0');
    }


  return d;
}


int
stream_reader::
read_decimal_integer() noexcept
{
  int  i = 0;

    while((*m_pointer >= '0') &&
          (*m_pointer <= '9'))
    {
      i *= 10;

      i += (*m_pointer++)-'0';
    }


  return i;
}


double
stream_reader::
read_decimal_fraction() noexcept
{
  double  d = 0.0;
  double  f = 1.0;

    while((*m_pointer >= '0') &&
          (*m_pointer <= '9'))
    {
      f /= 10;

      d += f*((*m_pointer++)-'0');
    }


  return d;
}


int
stream_reader::
read_hexadecimal_integer() noexcept
{
  int  i = 0;

    for(;;)
    {
      auto  c = *m_pointer;

        if((c >= '0') &&
           (c <= '9'))
        {
          i <<= 4;

          i += c-'0';

          ++m_pointer;
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


          ++m_pointer;
        }

      else
        {
          break;
        }
    }


  return i;
}


double
stream_reader::
read_hexadecimal_fraction() noexcept
{
  double  d = 0.0;
  double  f = 1.0;

    for(;;)
    {
      auto  c = *m_pointer;

        if((c >= '0') &&
           (c <= '9'))
        {
          f /= 16;

          d += f*(c-'0');

          ++m_pointer;
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


          ++m_pointer;
        }

      else
        {
          break;
        }
    }


  return d;
}


value
stream_reader::
read_number_that_begins_by_zero() noexcept
{
  auto  c = *m_pointer++;

  return ((c == 'b') || (c == 'B'))? read_binary_number()
        :((c == 'o') || (c == 'O'))? read_octal_number()
        :((c == 'x') || (c == 'X'))? read_hexadecimal_number()
        :((c == '.')              )? value(read_decimal_fraction())
        : value(0);
}




}




