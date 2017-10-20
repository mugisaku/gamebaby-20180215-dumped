#include"Square.hpp"
#include"Piece.hpp"
#include"Board.hpp"




namespace gmbb{




void
Square::
reset(int  x_, int  y_, SquareLinkSet&  lnset) noexcept
{
  x = x_;
  y = y_;

  linkset = lnset;
}




namespace{
Direction
next_direction(Direction  d) noexcept
{
    if(static_cast<int>(d) >= static_cast<int>(Direction::last))
    {
      return static_cast<Direction>(0);
    }


  return static_cast<Direction>(static_cast<int>(d)+1);
}
}


covered_ptr<Square>
Square::
put_item(GameItem const&  i, distance_t  d) noexcept
{
  set_distance(d);

    if(can_put_item())
    {
      item = i;

      return this;
    }


    if(d--)
    {
        for(int  n = 0;  n < 8;  ++n)
        {
          auto  ln = (*this)[static_cast<Direction>(n)];

            if(ln && (ln->get_distance() < d))
            {
              auto  res = ln->put_item(i,d);

                if(res)
                {
                  return res;
                }
            }
        }
    }


  return nullptr;
}




void
Square::
remove_piece() noexcept
{
    if(piece_ptr)
    {
      auto&  brd = piece_ptr->get_board();

      brd.delete_piece(piece_ptr);

      piece_ptr = nullptr;
    }
}


}




