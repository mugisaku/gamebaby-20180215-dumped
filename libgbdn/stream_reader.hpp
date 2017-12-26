#ifndef LIBGBDN_StreamReader_HPP
#define LIBGBDN_StreamReader_HPP


#include"value.hpp"
#include<cstdarg>
#include<cstdio>


namespace gbdn{
namespace gbdn_types{


class
stream_context
{
  const char*  m_header;

  int  m_line_number=1;

protected:
  const char*  m_pointer;

public:
  stream_context(const char*  p=nullptr) noexcept: m_header(p), m_pointer(p){}

  int  get_line_number() const noexcept{return m_line_number;}
  const char*  get_pointer() const noexcept{return m_pointer;}

  void  newline() noexcept
  {
    m_header = m_pointer;

    ++m_line_number;
  }

  void  print() const noexcept
  {
    printf("[エラー: %4d行目] ",m_line_number);

    const char*  p = m_header;

      if(p)
      {
          while(p < m_pointer)
          {
            fputc(*p++,stdout);
          }
      }
  }

};


class
stream_error: public stream_context
{
  char  m_buf[256];

public:
  stream_error(const stream_context&  ctx, const char*  fmt, ...):
  stream_context(ctx)
  {
    va_list  ap;
    va_start(ap,fmt);

    vsnprintf(m_buf,sizeof(m_buf),fmt,ap);

    va_end(ap);
  }

  void  print() const noexcept
  {
    stream_context::print();

    printf("\n: %s\n",m_buf);
  }

};



class list;


class
stream_reader: public stream_context
{
  char*  m_buffer=nullptr;

  size_t            m_length=0;
  size_t  m_allocated_length=0;

  string  read_identifier() noexcept;
  string  read_string(char  close_char) noexcept;

  int     read_binary_integer() noexcept;
  double  read_binary_fraction() noexcept;
  value  read_binary_number() noexcept;

  int  read_octal_integer() noexcept;
  double  read_octal_fraction() noexcept;
  value  read_octal_number() noexcept;

  int  read_decimal_integer() noexcept;
  double  read_decimal_fraction() noexcept;
  value  read_decimal_number() noexcept;

  int     read_hexadecimal_integer() noexcept;
  double  read_hexadecimal_fraction() noexcept;
  value  read_hexadecimal_number() noexcept;

  value  read_number_that_begins_by_zero() noexcept;

  void  clear_buffer() noexcept;

  void  push(char  c) noexcept;

  void  allocate_initial_buffer() noexcept;

  void  skip_linestyle_comment();
  void  skip_blockstyle_comment();

public:
  stream_reader() noexcept{allocate_initial_buffer();}
  stream_reader(const char*  p) noexcept: stream_context(p){allocate_initial_buffer();}
 ~stream_reader(){delete[] m_buffer;}

  void  skip_spaces() noexcept;

  void  advance(int  n) noexcept{m_pointer += n;}

  char  get_char() const noexcept{return *m_pointer;}

  value  read_value();

};


}


using gbdn_types::stream_context;
using gbdn_types::stream_error;
using gbdn_types::stream_reader;


}




#endif




