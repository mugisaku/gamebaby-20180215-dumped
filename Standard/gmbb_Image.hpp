#ifndef GMBB_IMAGE_HPP
#define GMBB_IMAGE_HPP


#include<cstdint>
#include<vector>
#include<string>
#include<memory>
#include"gmbb_GlyphSet.hpp"
#include"gmbb_FileReader.hpp"
#include"gmbb_Figures.hpp"
#include"gmbb_Palette.hpp"




namespace gmbb{


struct
Pixel
{
  ColorIndex  index=0;

  int16_t  z=0;

  constexpr Pixel(ColorIndex  i=ColorIndex(), int16_t  z_=0) noexcept:
  index(i), z(z_){}

};


constexpr ColorIndex
default_coloring[] = {0,white,0,0};


class
Image
{
  int  width;
  int  height;

  std::vector<Pixel>  pixels;

public:
  Image() noexcept{}
  Image(int  w, int  h) noexcept;


  void  resize(int  w, int  h) noexcept;

  void  load_png(FileReader&  r) noexcept;

  int   get_width() const noexcept{return this->width ;}
  int  get_height() const noexcept{return this->height;}

        Pixel&        get_pixel(int  x, int  y)       noexcept{return this->pixels[this->width*y+x];}
  const Pixel&  get_const_pixel(int  x, int  y) const noexcept{return this->pixels[this->width*y+x];}

  uint32_t  get_pixel_color(int  x, int  y, Palette const&  pal) const noexcept;

  void  fill(Pixel  pix=Pixel()) noexcept;


  void  draw_dot(       Point  pt, ColorIndex  i) noexcept;
  void  draw_dot_safely(Point  pt, ColorIndex  i) noexcept;

  void  draw_dot(       Point  pt, Pixel  pix) noexcept;
  void  draw_dot_safely(Point  pt, Pixel  pix) noexcept;

  void  draw_vline(       Point  pt, int  l, Pixel  pix) noexcept;
  void  draw_vline_safely(Point  pt, int  l, Pixel  pix) noexcept;
  void  draw_hline(       Point  pt, int  l, Pixel  pix, int  interval=0) noexcept;
  void  draw_hline_safely(Point  pt, int  l, Pixel  pix) noexcept;

  void  draw_line(Line  line, Pixel  pix) noexcept;

  void  draw_rectangle(       Rectangle const&  rect, Pixel  pix) noexcept;
  void  draw_rectangle_safely(Rectangle const&  rect, Pixel  pix) noexcept;
  void  fill_rectangle(       Rectangle         rect, Pixel  pix) noexcept;

  void  print(      char16_t   c, Point  pt, GlyphSet const&  glset, ColorIndex const*  coloring=default_coloring) noexcept;
  void  print(const char*      s, Point  pt, GlyphSet const&  glset, ColorIndex const*  coloring=default_coloring) noexcept;
  void  print(const char16_t*  s, Point  pt, GlyphSet const&  glset, ColorIndex const*  coloring=default_coloring) noexcept;

  void  transfer(Image const&  src, Rectangle  src_rect, Point  dst_pt, int  z=0) noexcept;

};


}




#endif




