#include"Event.hpp"




namespace gmbb{


Event::
Event(PieceEvent  p) noexcept:
kind(EventKind::piece)
{
  data.piece_event = p;
}


Event::
Event(SquareEvent  sq) noexcept:
kind(EventKind::square)
{
  data.square_event = sq;
}


Event::
Event(MessageEvent  msg) noexcept:
kind(EventKind::message)
{
  data.message_event = msg;
}


}




