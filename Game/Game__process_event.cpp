#include"Game_private.hpp"
#include"EventQueue.hpp"


namespace gmbb{


namespace{


void
process_message_event(MessageEvent const&  evt) noexcept
{
  start_message(evt.content);
}


void
process_piece_event(PieceEvent const&  evt) noexcept
{
  static std::string const  none("none");

    switch(evt.kind)
    {
  case(PieceEventKind::talk):
    {
      auto  talk = find_talk(evt.piece->get_name(),evt.guest? evt.guest->get_name():none);

        if(talk)
        {
          start_message(talk->data());
        }
    }
      break;
  case(PieceEventKind::push):
      printf("piece pushed\n");
      break;
  case(PieceEventKind::start_move):
      printf("started move\n");
      break;
  case(PieceEventKind::end_move):
      printf("ended move\n");
      break;
  case(PieceEventKind::collide_with_flying_item):
      printf("collided with flying item!\n");
      break;
  case(PieceEventKind::null):
      break;
  default:
      printf("error\n");
    }
}


void
process_square_event(SquareEvent const&  evt) noexcept
{
    switch(evt.kind)
    {
  case(SquareEventKind::piece_turn):
      printf("piece turned!\n");
      break;
  case(SquareEventKind::piece_enter):
      printf("piece entered into %2d,%2d!\n",evt.square->get_x(),evt.square->get_y());
      break;
  case(SquareEventKind::piece_leave):
      printf("piece left from %2d,%2d!\n",evt.square->get_x(),evt.square->get_y());
      break;
  case(SquareEventKind::piece_insert):
      break;
  case(SquareEventKind::piece_remove):
      break;
  case(SquareEventKind::piece_push):
      printf("piece pushed!\n");
      break;
  case(SquareEventKind::flying_item_enter):
      printf("flying item entered!\n");
      break;
  case(SquareEventKind::flying_item_leave):
      printf("flying item left!\n");
      break;
  case(SquareEventKind::flying_item_collide_with_wall):
      printf("flying item collided with wall!\n");
      break;
  case(SquareEventKind::flying_item_collide_with_piece):
      printf("flying item collided with piece!\n");
      break;
  case(SquareEventKind::flying_item_erase):
      printf("flying item erased!\n");
      break;
  case(SquareEventKind::null):
      printf("null\n");
      break;
  default:
      printf("error\n");
    }
}


}


void
process_event() noexcept
{
    while(event_queue::get_number_of_events())
    {
      auto  evt = event_queue::pop();

        switch(evt.get_kind())
        {
      case(EventKind::piece  ): process_piece_event( evt->piece_event);break;
      case(EventKind::square ): process_square_event(evt->square_event);break;
      case(EventKind::message): process_message_event(evt->message_event);break;
        }
    }
}


}




