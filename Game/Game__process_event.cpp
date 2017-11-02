#include"Game_private.hpp"
#include"EventQueue.hpp"


//#define dbg_printf(...)  printf(__VA_ARGS__)
#ifndef dbg_printf
#define dbg_printf(...)
#endif


namespace gmbb{


void
process_event() noexcept
{
    while(event_queue::get_number_of_events())
    {
      static Event  evt;

      event_queue::pull(evt);

        switch(evt.kind)
        {
      case(EventKind::message_Start):
          break;
      case(EventKind::message_End):
          break;
      case(EventKind::piece_Talk):
          break;
      case(EventKind::piece_Push_piece):
          break;
      case(EventKind::piece_Push_wall):
          break;
      case(EventKind::piece_Start_move):
          break;
      case(EventKind::piece_End_move):
          break;
      case(EventKind::piece_Turn):
          break;
      case(EventKind::piece_Enter_into_square):
          break;
      case(EventKind::piece_Leave_from_square):
          break;
      case(EventKind::piece_Insert_into_square):
          break;
      case(EventKind::piece_Remove_from_square):
          break;
      case(EventKind::flying_item_Enter_into_square):
          break;
      case(EventKind::flying_item_Leave_from_square):
          break;
      case(EventKind::flying_item_Collide_with_wall):
          break;
      case(EventKind::flying_item_Collide_with_piece):
          break;
      case(EventKind::flying_item_Erase):
          break;
      case(EventKind::shop_Enter):
          break;
      case(EventKind::shop_Buy_item):
          break;
      case(EventKind::shop_Sell_item):
          break;
      case(EventKind::shop_Exit):
          break;
      default:
          printf("[process event error] unkonwn event\n");
        }
    }
}


}




