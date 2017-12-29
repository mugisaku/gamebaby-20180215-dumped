#ifndef GMBB_StringBuffer_HPP
#define GMBB_StringBuffer_HPP


#include<string>
#include<cstdint>
#include<cstddef>
#include<cstdarg>


namespace gmbb{


class
StringBuffer
{
  char  data[256];

public:
  StringBuffer() noexcept{data[0] = 0;}
  StringBuffer(const char*  fmt, ...) noexcept;

  const char*  operator()() const noexcept{return data;}
  const char*  operator()(const char*  fmt, ...) noexcept;

};


}




#endif




