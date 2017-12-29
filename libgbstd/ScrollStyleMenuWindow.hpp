#ifndef GMBB_ScrollStyleMenuWindow_HPP_INCLUDED
#define GMBB_ScrollStyleMenuWindow_HPP_INCLUDED


#include"gmbb_Figures.hpp"
#include"gmbb_Window.hpp"
#include"gmbb_Menu.hpp"




namespace gmbb{




class
ScrollStyleMenuWindow: public Window
{
  Menu  menu;

  int  column_number;
  int     row_number;

  int  y_base=0;

  Point  cursor;

public:
  ScrollStyleMenuWindow(Menu  menu_, int  col_n, int  row_n, Point  pt) noexcept;

  int  get_item_index() const noexcept{return (column_number*(y_base+cursor.y))+cursor.x;}

  void  move_cursor_to_left()  noexcept;
  void  move_cursor_to_right() noexcept;
  void  move_cursor_to_up()    noexcept;
  void  move_cursor_to_down()  noexcept;

  void  reset_cursor() noexcept;

  void  render(Image&  dst, Point  offset) const noexcept override;

};


}




#endif




