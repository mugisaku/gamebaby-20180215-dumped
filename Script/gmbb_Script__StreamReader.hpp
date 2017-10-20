#ifndef GMBB_Script__StreamReader_HPP
#define GMBB_Script__StreamReader_HPP


#include"gmbb_Script__Token.hpp"
#include<cstdarg>


namespace gmbb{
namespace script{


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



class TokenString;


class
StreamReader: public StreamContext
{
  std::string  read_identifier() noexcept;
  std::string  read_string() noexcept;

  int  read_decimal_integer() noexcept;
  int  read_integer_that_begins_by_zero() noexcept;

  TokenString*  read_token_string(covered_ptr<TokenString>  parent, char  opening, char  closing);

public:
  StreamReader() noexcept{}
  StreamReader(char const*  p) noexcept: StreamContext(p){}

  void  skip_spaces() noexcept;

  void  advance(int  n) noexcept{pointer += n;}

  char  get_char() const noexcept{return *pointer;}

  Token  operator()(covered_ptr<TokenString>  parent=nullptr);

};


std::string  make_string_from_file(const char*  filepath);


}}




#endif




