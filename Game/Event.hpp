#ifndef GMBB_Event_HPP
#define GMBB_Event_HPP


#include"Shop.hpp"
#include"Piece.hpp"
#include"Square.hpp"


namespace gmbb{


enum class
EventKind
{
  null,

  message_Start,
  message_End,

  piece_Talk,
  piece_Turn,
  piece_Push_piece,
  piece_Push_wall,
  piece_Start_move,
  piece_End_move,
  piece_Enter_into_square,
  piece_Leave_from_square,
  piece_Insert_into_square,
  piece_Remove_from_square,

  flying_item_Enter_into_square,
  flying_item_Leave_from_square,
  flying_item_Collide_with_wall,
  flying_item_Collide_with_piece,
  flying_item_Erase,

  shop_Enter,
  shop_Buy_item,
  shop_Sell_item,
  shop_Exit,

};


struct
MessageEvent
{
  EventKind  kind;

  char const*  content;

};


struct
PieceEvent
{
  EventKind  kind;

  covered_ptr<Piece>          piece;
  covered_ptr<Piece>  another_piece;

  covered_ptr<Square>   square;

  covered_ptr<GameItem>  item;

};


struct
FlyingItemEvent
{
  EventKind  kind;

  covered_ptr<GameItem>  item;
  covered_ptr<Piece>    piece;
  covered_ptr<Square>   square;

};


struct
SquareEvent
{
  EventKind  kind;

  covered_ptr<Square>   square;
  covered_ptr<Piece>     piece;
  covered_ptr<GameItem>   item;

};


struct
ShopEvent
{
  EventKind  kind;

  Commodity const*  commodity;

  int  number;

};


union
Event
{
  EventKind  kind;

  PieceEvent             piece;
  FlyingItemEvent  flying_item;
  SquareEvent           square;
  MessageEvent         message;
  ShopEvent               shop;

  Event(EventKind  k=EventKind::null) noexcept: kind(k){}
 ~Event(){}

};


}




#endif




