#include"gmbb_FileReader.hpp"
#include<cstdio>




namespace gmbb{




FileReader::
FileReader(const char*  p, size_t  length) noexcept:
begin(p),
current(p),
end(p+length)
{
}




int
FileReader::
get() noexcept
{
  unsigned char  v = *current++;

  return v;
}


int
FileReader::
get_be16() noexcept
{
  int  v = get()<<8;

  v |= get();

  return v;
}


int
FileReader::
get_be32() noexcept
{
  int  v = get()<<24;

  v |= get()<<16;
  v |= get()<< 8;
  v |= get()    ;

  return v;
}




}




