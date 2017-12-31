#ifndef GMBB_UNICODE_HPP
#define GMBB_UNICODE_HPP


#include<string>
#include<cstdint>
#include<cstddef>


namespace gbstd{
namespace unicodes{


class
utf8_decoder
{
  const char*  m_pointer=nullptr;
  const char*  m_end=nullptr;

public:
  utf8_decoder(                    ) noexcept{}
  utf8_decoder(std::string_view  sv) noexcept{*this = sv;}

  utf8_decoder&  operator=(std::string_view  sv) noexcept
  {
    m_pointer = sv.data();
    m_end     = sv.data()+sv.size();

    return *this;
  }

  operator bool() const noexcept{return m_pointer < m_end;}

  char32_t  operator()() noexcept;

  const char*  get_pointer() const noexcept{return m_pointer;}
  const char*  get_end() const noexcept{return m_end;}

};


size_t  u8slen(std::string_view  sv) noexcept;

std::u16string  to_u16string(std::string_view     sv) noexcept;
std::string     to_string(std::u16string_view  u16sv) noexcept;


struct
utf8_encoder
{
  char  codes[8];

  utf8_encoder(char32_t  c=0) noexcept{*this = c;}

  utf8_encoder&  operator=(char32_t  c) noexcept;

};


}


using unicodes::utf8_decoder;
using unicodes::utf8_encoder;
using unicodes::u8slen;
using unicodes::to_u16string;
using unicodes::to_string;


}




#endif




