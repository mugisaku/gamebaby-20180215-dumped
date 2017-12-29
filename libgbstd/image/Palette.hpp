#ifndef GMBB_Palette_HPP
#define GMBB_Palette_HPP


#include<cstdint>


namespace gmbb{


struct
ColorIndex
{
  uint16_t  code;

  constexpr ColorIndex(uint16_t  code_=0) noexcept: code(code_){}
  constexpr ColorIndex(int  ri, int  gi, int  bi) noexcept: code(01000|(ri<<6)|(gi<<3)|bi){}

  constexpr operator bool() const noexcept{return code>>9;}

  constexpr int  r() const noexcept{return (code>>6)&07;}
  constexpr int  g() const noexcept{return (code>>3)&07;}
  constexpr int  b() const noexcept{return (code   )&07;}

  constexpr int  r255() const noexcept{return (((code>>6)&07)<<5)|0b11111;}
  constexpr int  g255() const noexcept{return (((code>>3)&07)<<5)|0b11111;}
  constexpr int  b255() const noexcept{return (((code   )&07)<<5)|0b11111;}

};


namespace predefined_color_index{
constexpr ColorIndex        null(00000);
constexpr ColorIndex       white(01777);
constexpr ColorIndex       black(01000);
constexpr ColorIndex        gray(01333);
constexpr ColorIndex  light_gray(01555);
constexpr ColorIndex   dark_gray(01111);
constexpr ColorIndex         red(01700);
constexpr ColorIndex       green(01070);
constexpr ColorIndex        blue(01007);
constexpr ColorIndex      yellow(01770);
}


using namespace predefined_color_index;


class
Palette
{
  uint32_t  color_table[01000];

public:
  void  set_color(ColorIndex  i, uint32_t  value) noexcept{this->color_table[i.code&0777] = value;}

  uint32_t  get_color(ColorIndex  i) const noexcept{return this->color_table[i.code&0777];};

};


}


#endif




