#ifndef GMBB_Event__Piece_HPP
#define GMBB_Event__Piece_HPP


#include"covered_ptr"


namespace gmbb{


class Piece;
class GameItem;


enum class
PieceEventKind
{
  null,
  talk,
  push,
  start_move,
  end_move,
  collide_with_flying_item,

};


enum class
PieceEventSubKind: int;


struct
PieceEvent
{
  PieceEventKind         kind;
  PieceEventSubKind  sub_kind;

  covered_ptr<Piece>  piece;
  covered_ptr<Piece>  guest;
  covered_ptr<GameItem>  item;

  PieceEvent(PieceEventKind  k, covered_ptr<Piece>  piece_, covered_ptr<Piece>  guest_, covered_ptr<GameItem>  i=nullptr) noexcept:
  kind(k),
  piece(piece_), guest(guest_), item(i){}

};


}




#endif




