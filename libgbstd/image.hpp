#ifndef GMBB_IMAGE_HPP
#define GMBB_IMAGE_HPP


#include<cstdint>
#include<vector>
#include<string>
#include"libgbstd/font.hpp"
#include"libgbstd/figures.hpp"
#include"libgbstd/ro_ptr.hpp"




namespace gbstd{
namespace images{


struct
color_index
{
  uint16_t  code;

  constexpr color_index(uint16_t  code_=0) noexcept: code(code_){}
  constexpr color_index(int  ri, int  gi, int  bi) noexcept: code(01000|(ri<<6)|(gi<<3)|bi){}

  constexpr operator bool() const noexcept{return code>>9;}

  constexpr int  get_r() const noexcept{return (code>>6)&07;}
  constexpr int  get_g() const noexcept{return (code>>3)&07;}
  constexpr int  get_b() const noexcept{return (code   )&07;}

  constexpr int  get_r255() const noexcept{return (((code>>6)&07)<<5)|0b11111;}
  constexpr int  get_g255() const noexcept{return (((code>>3)&07)<<5)|0b11111;}
  constexpr int  get_b255() const noexcept{return (((code   )&07)<<5)|0b11111;}

};


namespace predefined{
constexpr color_index        null(00000);
constexpr color_index       white(01777);
constexpr color_index       black(01000);
constexpr color_index        gray(01333);
constexpr color_index  light_gray(01555);
constexpr color_index   dark_gray(01111);
constexpr color_index         red(01700);
constexpr color_index       green(01070);
constexpr color_index        blue(01007);
constexpr color_index      yellow(01770);
}


class
palette
{
  uint32_t  m_color_table[01000];

public:
  void  set_color(color_index  i, uint32_t  value) noexcept{m_color_table[i.code&0777] = value;}

  uint32_t  get_color(color_index  i) const noexcept{return m_color_table[i.code&0777];};

};


struct
pixel
{
  color_index  index=0;

  int16_t  z=0;

  constexpr pixel(color_index  i=color_index(), int16_t  z_=0) noexcept:
  index(i), z(z_){}

};


constexpr color_index
default_coloring[] = {0,predefined::white,0,0};


class
image
{
  int  m_width;
  int  m_height;

  std::vector<pixel>  m_pixels;

public:
  image() noexcept{}
  image(int  w, int  h) noexcept;


  void  resize(int  w, int  h) noexcept;

  void  load_png(binary_stream_reader&  r) noexcept;

  int   get_width() const noexcept{return m_width ;}
  int  get_height() const noexcept{return m_height;}

        pixel&        get_pixel(int  x, int  y)       noexcept{return m_pixels[m_width*y+x];}
  const pixel&  get_const_pixel(int  x, int  y) const noexcept{return m_pixels[m_width*y+x];}

  uint32_t  get_pixel_color(int  x, int  y, palette const&  pal) const noexcept;

  void  fill(pixel  pix=pixel()) noexcept;

  void  add(int  r, int  g, int  b) noexcept;
  void  reverse_color() noexcept;


  void  draw_dot(       point  pt, color_index  i) noexcept;
  void  draw_dot_safely(point  pt, color_index  i) noexcept;

  void  draw_dot(       point  pt, pixel  pix) noexcept;
  void  draw_dot_safely(point  pt, pixel  pix) noexcept;

  void  draw_vline(       point  pt, int  l, pixel  pix) noexcept;
  void  draw_vline_safely(point  pt, int  l, pixel  pix) noexcept;
  void  draw_hline(       point  pt, int  l, pixel  pix, int  interval=0) noexcept;
  void  draw_hline_safely(point  pt, int  l, pixel  pix) noexcept;

  void  draw_line(line  ln, pixel  pix) noexcept;

  void  draw_rectangle(       rectangle const&  rect, pixel  pix) noexcept;
  void  draw_rectangle_safely(rectangle const&  rect, pixel  pix) noexcept;
  void  fill_rectangle(       rectangle         rect, pixel  pix) noexcept;

  void  print(char16_t   c, point  pt, const font&  fnt, ro_ptr<color_index>  coloring=default_coloring) noexcept;
  void  print(std::string_view     sv, point  pt, const font&  fnt, ro_ptr<color_index>  coloring=default_coloring) noexcept;
  void  print(std::u16string_view  sv, point  pt, const font&  fnt, ro_ptr<color_index>  coloring=default_coloring) noexcept;

  void  transfer(image const&  src, rectangle  src_rect, point  dst_pt, int  z=0) noexcept;

};


}


using images::color_index;
using images::palette;
using images::predefined::null;
using images::predefined::white;
using images::predefined::black;
using images::predefined::red;
using images::predefined::green;
using images::predefined::blue;
using images::predefined::yellow;
using images::predefined::gray;
using images::predefined::light_gray;
using images::predefined::dark_gray;

using images::image;
using images::pixel;


}




#endif




