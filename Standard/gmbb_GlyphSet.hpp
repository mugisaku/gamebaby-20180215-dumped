#ifndef GMBB_GlyphSet_HPP_INCLUDED
#define GMBB_GlyphSet_HPP_INCLUDED


#include<cstdint>
#include<cstdio>
#include<cstddef>
#include<string>


namespace gmbb{


class
GlyphSet
{
  uint32_t*  link_table[0x10000-256]={0};

  int   width=0;
  int  height=0;

  int  bits_per_pixel=0;

public:
  GlyphSet() noexcept{}
  GlyphSet(GlyphSet const&  rhs) noexcept=delete;
  GlyphSet(GlyphSet&&       rhs) noexcept=delete;
 ~GlyphSet(){clear();}


  GlyphSet&  operator=(GlyphSet const&  rhs) noexcept=delete;
  GlyphSet&  operator=(GlyphSet&&       rhs) noexcept=delete;

  void  clear() noexcept;

  int   get_width() const noexcept{return this->width ;}
  int  get_height() const noexcept{return this->height;}
  int  get_bits_per_pixel() const noexcept{return this->bits_per_pixel;}

  uint32_t const*  get_glyph_data(char16_t  c) const noexcept;

  void  load_from_file(char const*  path) noexcept;
  void  load_from_file(FILE*  f) noexcept;

  void  save_to_file(char const*  path) const noexcept;
  void  save_to_file(FILE*  f) const noexcept;

};


}


#endif




