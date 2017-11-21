#include"gmbb_StringBuffer.hpp"




namespace gmbb{




StringBuffer::
StringBuffer(const char*  fmt, ...) noexcept
{
  va_list  ap;
  va_start(ap,fmt);

  vsnprintf(data,sizeof(data),fmt,ap);

  va_end(ap);
}




const char*
StringBuffer::
operator()(const char*  fmt, ...) noexcept
{
  va_list  ap;
  va_start(ap,fmt);

  vsnprintf(data,sizeof(data),fmt,ap);

  va_end(ap);


  return data;
}




}




