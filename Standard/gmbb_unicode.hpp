#ifndef GMBB_UNICODE_HPP
#define GMBB_UNICODE_HPP


#include<string>
#include<cstdint>
#include<cstddef>
#include<cstdarg>
#include"Pointer.hpp"


namespace gmbb{


struct not_utf8{};
struct not_utf32{};
struct invalid_utf8_byte_number{};


size_t  utf8_byte_number(unsigned char  c);


size_t  u8slen(ro_ptr<char>  s) noexcept;


char32_t  to_char32(ro_ptr<char>  utf8, size_t  byte_number);

std::u16string  to_u16string(ro_ptr<char>  s);
std::string     to_string(ro_ptr<char16_t>  u16s);


struct
UTF8Chunk
{
  char  codes[8];

  UTF8Chunk(char32_t  c=0);

  UTF8Chunk&  operator=(char32_t  c);

};


}




#endif




