#include"libgbstd/text.hpp"




namespace gbstd{
namespace texts{


namespace{


constexpr size_t  buffer_size = 1024;

char  buffer[buffer_size];


}


std::string_view
make_text(const char*  fmt, ...) noexcept
{
  va_list  ap;
  va_start(ap,fmt);

  auto  n = vsnprintf(buffer,sizeof(buffer),fmt,ap);

  va_end(ap);

    if(n >= buffer_size)
    {
      return std::string_view("バッファが足りない");
    }


  return std::string_view(buffer,n);
}




}}




