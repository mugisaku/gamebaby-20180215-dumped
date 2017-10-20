#ifndef GMBB_Event__Square_HPP
#define GMBB_Event__Square_HPP


#include"covered_ptr"


namespace gmbb{


class   Square;
class    Piece;
class GameItem;


enum class
SquareEventKind
{
  null,
  piece_turn,
  piece_enter,
  piece_leave,
  piece_insert,
  piece_remove,
  piece_push,
  flying_item_enter,
  flying_item_leave,
  flying_item_collide_with_wall,
  flying_item_collide_with_piece,
  flying_item_erase,

};


union
SquareEventData
{
   SquareEventData(){}
  ~SquareEventData(){}

};


struct
SquareEvent
{
  SquareEventKind  kind;

  covered_ptr<Square>   square;
  covered_ptr<Piece>     piece;
  covered_ptr<GameItem>   item;

  SquareEvent(SquareEventKind  k, covered_ptr<Square>  sq, covered_ptr<Piece>  p, covered_ptr<GameItem>  i) noexcept:
  kind(k),
  square(sq),
  piece(p),
  item(i){}

};


}




#endif




