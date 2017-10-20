#ifndef GMBB_Event_HPP
#define GMBB_Event_HPP


#include"Event__Piece.hpp"
#include"Event__Square.hpp"


namespace gmbb{


enum class
EventKind
{
  null,
  message,
  piece,
  square

};


struct
MessageEvent
{
  char const*  content;

};


union
EventData
{
  PieceEvent      piece_event;
  SquareEvent    square_event;
  MessageEvent  message_event;

   EventData(){}
  ~EventData(){}
};


class
Event
{
  EventKind  kind=EventKind::null;
  EventData  data;

public:
  Event() noexcept{}
  Event(PieceEvent      p) noexcept;
  Event(SquareEvent    sq) noexcept;
  Event(MessageEvent  msg) noexcept;

  EventKind  get_kind() const noexcept{return kind;}

  EventData const*  operator->() const noexcept{return &data;}

};


}




#endif




