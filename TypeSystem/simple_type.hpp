#ifndef simple_type_HPP
#define simple_type_HPP


#include<cstdint>
#include<cstddef>



namespace ts{
namespace types{


struct
unsign_specifier
{
};


class
simple_type
{
  bool     m_unsigned_flag;
  uint8_t  m_bit_width;

public:
  constexpr simple_type(uint8_t  bit_width) noexcept:
  m_unsigned_flag(false),
  m_bit_width(bit_width){}

  constexpr simple_type(unsign_specifier  unsign, uint8_t  bit_width) noexcept:
  m_unsigned_flag(true),
  m_bit_width(bit_width){}

  constexpr bool  is_unsigned() const noexcept{return m_unsigned_flag;}

  constexpr size_t  get_bit_width() const noexcept{return m_bit_width;}

  constexpr size_t  get_size() const noexcept{return m_bit_width/8;}

};


}


using types::unsign_specifier;
using types::simple_type;


}


#endif




