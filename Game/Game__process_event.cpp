#include"Game_private.hpp"
#include"EventQueue.hpp"


//#define dbg_printf(...)  printf(__VA_ARGS__)
#ifndef dbg_printf
#define dbg_printf(...)
#endif


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
      auto  data = evt.guest->find_talk_data(evt.piece->get_name());

        if(data)
        {
          evt.guest->change_direction(get_opposite(evt.piece->get_direction()));

          start_message(data->content.data());
        }

      else
        {
          start_message("かいわデータがありません\n");
        }
    }
      break;
  case(PieceEventKind::push):
      dbg_printf("piece pushed\n");
      break;
  case(PieceEventKind::start_move):
      dbg_printf("started move\n");
      break;
  case(PieceEventKind::end_move):
      dbg_printf("ended move\n");
      break;
  case(PieceEventKind::collide_with_flying_item):
      dbg_printf("collided with flying item!\n");
      break;
  case(PieceEventKind::null):
      break;
  default:
      dbg_printf("error\n");
    }
}


void
process_square_event(SquareEvent const&  evt) noexcept
{
    switch(evt.kind)
    {
  case(SquareEventKind::piece_turn):
      dbg_printf("piece turned!\n");
      break;
  case(SquareEventKind::piece_enter):
      dbg_printf("piece entered into %2d,%2d!\n",evt.square->get_x(),evt.square->get_y());
      break;
  case(SquareEventKind::piece_leave):
      dbg_printf("piece left from %2d,%2d!\n",evt.square->get_x(),evt.square->get_y());
      break;
  case(SquareEventKind::piece_insert):
      break;
  case(SquareEventKind::piece_remove):
      break;
  case(SquareEventKind::piece_push):
      dbg_printf("piece pushed!\n");
      break;
  case(SquareEventKind::flying_item_enter):
      dbg_printf("flying item entered!\n");
      break;
  case(SquareEventKind::flying_item_leave):
      dbg_printf("flying item left!\n");
      break;
  case(SquareEventKind::flying_item_collide_with_wall):
      dbg_printf("flying item collided with wall!\n");
      break;
  case(SquareEventKind::flying_item_collide_with_piece):
      dbg_printf("flying item collided with piece!\n");
      break;
  case(SquareEventKind::flying_item_erase):
      dbg_printf("flying item erased!\n");
      break;
  case(SquareEventKind::null):
      dbg_printf("null\n");
      break;
  default:
      dbg_printf("error\n");
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




