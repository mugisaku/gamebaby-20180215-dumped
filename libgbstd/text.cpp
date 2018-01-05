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

  auto  sv = make_text_with_va_list(fmt,ap);

  va_end(ap);

  return sv;
}


std::string_view
make_text_with_va_list(const char*  fmt, va_list  ap) noexcept
{
  auto  n = vsnprintf(buffer,sizeof(buffer),fmt,ap);

    if(n >= buffer_size)
    {
      return std::string_view("バッファが足りない");
    }


  return std::string_view(buffer,n);
}


const char*
get_string(std::string_view  sv) noexcept
{
    if(*(sv.data()+sv.size()))
    {
      static std::string  s;

      s = sv;

      return s.data();
    }

  else
    {
      return sv.data();
    }
}


}}




