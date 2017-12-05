#ifndef LIBGBDN_StreamReader_HPP
#define LIBGBDN_StreamReader_HPP


#include"value.hpp"
#include<cstdarg>
#include<cstdio>


namespace gbdn{


class
stream_context
{
  const char*  header;

  int  line_number=1;

protected:
  const char*  pointer;

public:
  stream_context(char const*  p=nullptr) noexcept: header(p), pointer(p){}

  int  get_line_number() const noexcept{return line_number;}
  char const*  get_pointer() const noexcept{return pointer;}

  void  newline() noexcept
  {
    header = pointer;

    ++line_number;
  }

  void  print() const noexcept
  {
    printf("[エラー: %4d行目] ",line_number);

    char const*  p = header;

      if(p)
      {
          while(p < pointer)
          {
            fputc(*p++,stdout);
          }
      }
  }

};


class
stream_error: public stream_context
{
  char  buf[256];

public:
  stream_error(const stream_context&  ctx, const char*  fmt, ...):
  stream_context(ctx)
  {
    va_list  ap;
    va_start(ap,fmt);

    vsnprintf(buf,sizeof(buf),fmt,ap);

    va_end(ap);
  }

  void  print() const noexcept
  {
    stream_context::print();

    printf("\n: %s\n",buf);
  }

};



class list;


class
stream_reader: public stream_context
{
  char*  buffer=nullptr;

  size_t            length=0;
  size_t  allocated_length=0;

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
  stream_reader(char const*  p) noexcept: stream_context(p){allocate_initial_buffer();}
 ~stream_reader(){delete[] buffer;}

  void  skip_spaces() noexcept;

  void  advance(int  n) noexcept{pointer += n;}

  char  get_char() const noexcept{return *pointer;}

  value  read_value();

};


}




#endif




