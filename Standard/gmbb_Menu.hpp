#ifndef GMBB_Menu_HPP_INCLUDED
#define GMBB_Menu_HPP_INCLUDED


#include<cstdint>
#include<algorithm>
#include"gmbb_Figures.hpp"




namespace gmbb{


class Image;

using MenuItemRenderer = void  (*)(Image&  dst, Point  point, int  index);


class
Menu
{
  int  item_width;
  int  item_height;

  int  row_number;

  MenuItemRenderer  renderer;

public:
  constexpr Menu(int  item_w, int  item_h, int  row_n, MenuItemRenderer  rend) noexcept:
  item_width( item_w),
  item_height(item_h),
  row_number(row_n),
  renderer(rend){}

  constexpr int  get_item_width()  const noexcept{return item_width ;}
  constexpr int  get_item_height() const noexcept{return item_height;}

  constexpr int  get_row_number() const noexcept{return row_number;}
  constexpr int  get_image_height() const noexcept{return item_height*row_number;}

  void  set_row_number(int  n) noexcept{row_number = n;}

  void  render(Image&  dst, Point  dst_point, int  start_index, int  column_number=1) const noexcept;

};


}




#endif




