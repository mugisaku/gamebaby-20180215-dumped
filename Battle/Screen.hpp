#ifndef game_Screen_HPP
#define game_Screen_HPP


#include"gmbb_Standard.hpp"


namespace gmbb{
namespace screen{


constexpr int   width = 288;
constexpr int  height = 240;


void        set_fill_color(ColorIndex  i) noexcept;
ColorIndex  get_fill_color(             ) noexcept;

void   enable_add_color() noexcept;
void  disable_add_color() noexcept;

void   enable_reverse_color() noexcept;
void  disable_reverse_color() noexcept;

void   enable_render() noexcept;
void  disable_render() noexcept;

void  set_add_r(int  v) noexcept;
void  set_add_g(int  v) noexcept;
void  set_add_b(int  v) noexcept;

int  get_add_r() noexcept;
int  get_add_g() noexcept;
int  get_add_b() noexcept;


Image&  get_image() noexcept;

const Image&  update(const Task&  root_task) noexcept;

struct
Subtitle
{
  const char*  string;

  Point  point;

  const GlyphSet*  glyphset;

  Subtitle*  previous=nullptr;
  Subtitle*      next=nullptr;

};


void  insert_subtitle(Subtitle&  subt) noexcept;


}}




#endif




