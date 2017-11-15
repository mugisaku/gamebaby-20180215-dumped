#include"Board.hpp"


namespace gmbb{




namespace{
void
render_square(Square const&  sq, Image&  dst, Point  offset) noexcept
{
  Rectangle  rect(24*4,24*10,24,24);

    if(sq == SquareKind::room)
    {
      rect.y += 24;
    }


  dst.transfer(character_image,rect,offset,0);

  auto&  item = sq.get_item();

    if(item)
    {
      dst.transfer(character_image,get_rectangle_for_item(item),offset,0);
    }
}


void
render_row(Square const*  begin,
           Square const*  current,
           Square const*  end, Image&  dst, Point  offset) noexcept
{
    while(offset.x < screen::width)
    {
        if(current >= end)
        {
          current = begin;
        }


      render_square(*current++,dst,offset);

      offset.x += square_size;
    }
}
}


void
Board::
render(Image&  dst, Point  offset) const noexcept
{
  constexpr int  w = (screen::width /square_size);
  constexpr int  h = (screen::height/square_size);

  Point  start_point = view_point/square_size;
  Point    rem_point = view_point%square_size;

  int  dst_x = -rem_point.x;
  int  dst_y = -rem_point.y;

    while(dst_y < screen::height)
    {
        if(start_point.y >= board_height)
        {
          start_point.y = 0;
        }


      auto  line_begin = &get_const_square(0,start_point.y);
      auto       start = line_begin+start_point.x;
      auto    line_end = line_begin+board_width;

      render_row(line_begin,start,line_end,dst,Point(dst_x,dst_y));

      start_point.y +=           1;
              dst_y += square_size;
    }


  Piece const*  current = static_cast<Piece const*>(get_const_first());

    while(current)
    {
//        if(current->check_visible_count())
        {
          current->render(dst,-view_point);
        }


      current = static_cast<Piece const*>(current->get_const_next());
    }
}




}




