#include"gmbb_ScrollStyleMenuWindow.hpp"
#include"gmbb_environment.hpp"




namespace gmbb{


ScrollStyleMenuWindow::
ScrollStyleMenuWindow(Menu const&  menu_, int  col_n, int  row_n, Point  pt) noexcept:
menu(menu_),
column_number(col_n),
row_number(row_n)
{
  Window::resize(menu.get_item_width()*column_number+16,
                 menu.get_image_height()            +16);

  set_base_point(pt);
}




void
ScrollStyleMenuWindow::
reset_cursor() noexcept
{
  y_base = 0;

  cursor = Point();
}




void
ScrollStyleMenuWindow::
move_cursor_to_left()  noexcept
{
    if(cursor.x)
    {
      cursor.x -= 1;
    }
}


void
ScrollStyleMenuWindow::
move_cursor_to_right() noexcept
{
   if(cursor.x < (column_number-1))
   {
     cursor.x += 1;
   }
}


void
ScrollStyleMenuWindow::
move_cursor_to_up()    noexcept
{
       if(cursor.y){cursor.y -= 1;}
  else if(  y_base){y_base   -= 1;}
}


void
ScrollStyleMenuWindow::
move_cursor_to_down()  noexcept
{
       if(                      cursor.y < (menu.get_row_number()-1)){cursor.y += 1;}
  else if((y_base+menu.get_row_number()) < (         row_number  -1)){y_base   += 1;}
}




void
ScrollStyleMenuWindow::
render(Image&  dst, Point  offset) const noexcept
{
  Window::render(dst,offset);

    if(Window::get_state() == WindowState::full_opened)
    {
      Point  const base_offset(get_base_point()+offset+8);

      int  w = menu.get_item_width();
      int  h = menu.get_item_height();

      menu.render(dst,base_offset,(column_number*y_base),column_number);


      Rectangle  rect(base_offset.x+(w*cursor.x),
                      base_offset.y+(h*cursor.y),w,h);

      dst.draw_rectangle(rect,Pixel(yellow,30000));
    }
}




}




