#include"gmbb_StreamReader.hpp"
#include<cstdio>




namespace gmbb{




StreamReader::
StreamReader(const char*  p, size_t  length) noexcept:
begin(p),
current(p),
end(p+length)
{
}




int
StreamReader::
get() noexcept
{
  return static_cast<unsigned char>(*current++);
}


int
StreamReader::
get_be16() noexcept
{
  int  v = get()<<8;

  v |= get();

  return v;
}


int
StreamReader::
get_be32() noexcept
{
  int  v = get()<<24;

  v |= get()<<16;
  v |= get()<< 8;
  v |= get()    ;

  return v;
}




}




