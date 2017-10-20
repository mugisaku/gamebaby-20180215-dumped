#ifndef GMBB_ColumnStyleMenuWindow_HPP_INCLUDED
#define GMBB_ColumnStyleMenuWindow_HPP_INCLUDED


#include"gmbb_Figures.hpp"
#include"gmbb_Window.hpp"
#include"gmbb_Menu.hpp"




namespace gmbb{




class
ColumnStyleMenuWindow: public Window
{
  Menu  menu;

  int  page_index=0;
  int   row_index=0;

  int  page_number;

public:
  ColumnStyleMenuWindow(Menu const&  menu_, int  page_n, Point  pt) noexcept;

  int  get_item_index() const noexcept;

  void  move_cursor_to_left()  noexcept;
  void  move_cursor_to_right() noexcept;
  void  move_cursor_to_up()    noexcept;
  void  move_cursor_to_down()  noexcept;

  void  change_row_number(int  n) noexcept;

  void  reset_cursor() noexcept;

  void  render(Image&  dst, Point  offset) const noexcept override;

};


}




#endif




