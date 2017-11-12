#ifndef GAMN_StreamReader_HPP
#define GAMN_StreamReader_HPP


#include"gamn_Value.hpp"
#include"covered_ptr"
#include<cstdarg>


namespace gamn{


class
FileStream
{
  FILE*  f;

public:
  FileStream(char const*  filepath) noexcept: f(fopen(filepath,"rb")){}
 ~FileStream()
  {
      if(f)
      {
        fclose(f);
      }
  }


  char  getc() const noexcept{return fgetc(f);};

  operator bool() const noexcept{return f;}

  bool  eof()   const noexcept{return feof(f);}
  bool  error() const noexcept{return ferror(f);}

};


class
StreamContext
{
  char const*  header;

  int  line_number=1;

protected:
  char const*  pointer;

public:
  StreamContext(char const*  p=nullptr) noexcept: header(p), pointer(p){}

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
StreamError: public StreamContext
{
  char  buf[256];

public:
  StreamError(StreamContext const&  ctx, char const*  fmt, ...):
  StreamContext(ctx)
  {
    va_list  ap;
    va_start(ap,fmt);

    vsnprintf(buf,sizeof(buf),fmt,ap);

    va_end(ap);
  }

  void  print() const noexcept
  {
    StreamContext::print();

    printf("\n: %s\n",buf);
  }

};



class List;


struct
Contracept
{
  bool  value;

  explicit constexpr Contracept(bool  v) noexcept: value(v){}

};


class
StreamReader: public StreamContext
{
  std::string  read_identifier() noexcept;
  std::string  read_string() noexcept;

  int     read_binary_integer() noexcept;
  double  read_binary_fraction() noexcept;
  Value  read_binary_number() noexcept;

  int  read_octal_integer() noexcept;
  double  read_octal_fraction() noexcept;
  Value  read_octal_number() noexcept;

  int  read_decimal_integer() noexcept;
  double  read_decimal_fraction() noexcept;
  Value  read_decimal_number() noexcept;

  int     read_hexadecimal_integer() noexcept;
  double  read_hexadecimal_fraction() noexcept;
  Value  read_hexadecimal_number() noexcept;

  Value  read_number_that_begins_by_zero() noexcept;

  List*  read_list(covered_ptr<List>  parent, char  opening, char  closing);

  Value  read_child_value(std::string&&  s, covered_ptr<List>  parent);
  Value  read_pair(       std::string&&  s, covered_ptr<List>  parent);

public:
  StreamReader() noexcept{}
  StreamReader(char const*  p) noexcept: StreamContext(p){}

  void  skip_spaces() noexcept;

  void  advance(int  n) noexcept{pointer += n;}

  char  get_char() const noexcept{return *pointer;}

  Value  read_value(covered_ptr<List>  parent=nullptr, Contracept  contracept=Contracept(false));

};


}




#endif




