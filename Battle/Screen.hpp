#ifndef game_Screen_HPP
#define game_Screen_HPP


#include"libgbstd/image.hpp"
#include"libgbstd/task.hpp"
#include"libgbstd/ro_ptr.hpp"


namespace screen{


constexpr int   width = 288;
constexpr int  height = 240;


void                set_fill_color(gbstd::color_index  i) noexcept;
gbstd::color_index  get_fill_color(                     ) noexcept;

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


gbstd::image&  get_image() noexcept;

const gbstd::image&  update(const gbstd::task&  root_task) noexcept;

struct
Subtitle
{
  gbstd::ro_ptr<char>  string;

  gbstd::point  point;

  gbstd::ro_ptr<gbstd::font>  font;

  Subtitle*  previous=nullptr;
  Subtitle*      next=nullptr;

};


void  insert_subtitle(Subtitle&  subt) noexcept;


}




#endif




