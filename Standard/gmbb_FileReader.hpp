#ifndef GMBB_FILEREADER_HPP
#define GMBB_FILEREADER_HPP


#include<cstddef>




namespace gmbb{


class
FileReader
{
  char const*    begin;
  char const*      end;
  char const*  current;

public:
  FileReader(const char*  p, size_t  length) noexcept;

  void  rewind() noexcept{current = begin;}

  void  advance(size_t  n) noexcept{current += n;}

  int  get() noexcept;
  int  get_be16() noexcept;
  int  get_be32() noexcept;

  bool  test_eof() const noexcept{return current >= end;}

};


}




#endif




