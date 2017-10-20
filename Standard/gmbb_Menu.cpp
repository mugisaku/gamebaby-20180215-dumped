#include"gmbb_Menu.hpp"




namespace gmbb{




void
Menu::
render(Image&  dst, Point  dst_point, int  start_index, int  column_number) const noexcept
{
  int  current_index = start_index;

    for(int  y = 0;  y < row_number;  ++y)
    {
        for(int  x = 0;  x < column_number;  ++x)
        {
          renderer(dst,Point(dst_point.x+(item_width*x),dst_point.y),current_index++);
        }


      dst_point.y += item_height;
    }
}




}




