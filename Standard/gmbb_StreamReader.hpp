#ifndef GMBB_StreamReader_HPP
#define GMBB_StreamReader_HPP


#include<cstddef>




namespace gmbb{


class
StreamReader
{
  char const*    begin;
  char const*      end;
  char const*  current;

public:
  StreamReader(const char*  p, size_t  length) noexcept;

  void  rewind() noexcept{current = begin;}

  void  advance(size_t  n) noexcept{current += n;}

  int  get() noexcept;
  int  get_be16() noexcept;
  int  get_be32() noexcept;

  operator bool() const noexcept{return current < end;}

};


}




#endif




