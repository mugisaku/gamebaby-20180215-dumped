#include"binary_stream_reader.hpp"
#include<cstdio>




namespace gbstd{
namespace binary_streams{




binary_stream_reader::
binary_stream_reader(std::string_view  sv) noexcept:
m_begin(sv.data()),
m_current(sv.data()),
m_end(sv.data()+sv.size())
{
}




int
binary_stream_reader::
get() noexcept
{
  return static_cast<unsigned char>(*m_current++);
}


int
binary_stream_reader::
get_be16() noexcept
{
  int  v = get()<<8;

  v |= get();

  return v;
}


int
binary_stream_reader::
get_be32() noexcept
{
  int  v = get()<<24;

  v |= get()<<16;
  v |= get()<< 8;
  v |= get()    ;

  return v;
}




}}




