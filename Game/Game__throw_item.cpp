#include"Game_private.hpp"
#include"EventQueue.hpp"


namespace gmbb{




enum class
ActionIndex: int
{
  null,
  moving,
  message,
};




namespace{


bool
is_busy;


constexpr int  count_per_step = 12;


GameItem
thrown_item;


EffectObject
object;


covered_ptr<Square>
current_square;


Direction
moving_direction;


bool
check() noexcept
{
  auto  next = (*current_square)[moving_direction];

    if(next)
    {
        if(*next == SquareKind::wall)
        {
          board.clear_all_distance();

          current_square->put_item(thrown_item,3);

          effect_director.remove(object);

          event_queue::push(SquareEvent(SquareEventKind::flying_item_collide_with_wall,current_square,nullptr,&thrown_item));

          return true;
        }

      else
        if(next->get_piece())
        {
          auto  p = next->get_piece();

          event_queue::push(SquareEvent(SquareEventKind::flying_item_collide_with_piece,current_square,p,&thrown_item));
          event_queue::push(PieceEvent(PieceEventKind::collide_with_flying_item,p,nullptr,&thrown_item));

          effect_director.remove(object);

          return true;
        }

      else
        {
          event_queue::push(SquareEvent(SquareEventKind::flying_item_leave,current_square,nullptr,&thrown_item));
          event_queue::push(SquareEvent(SquareEventKind::flying_item_enter,          next,nullptr,&thrown_item));

          current_square = next;
        }
    }

  else
    {
      event_queue::push(SquareEvent(SquareEventKind::flying_item_erase,next,nullptr,&thrown_item));

      effect_director.remove(object);

      return true;
    }


  return false;
}


void
controll(EffectObject&  self) noexcept
{
    switch(self.get_action_index())
    {
  case(ActionIndex::null):
      break;
  case(ActionIndex::moving):
    {
        if(self.get_frame_count() >= (square_size/count_per_step))
        {
          self.reset_frame_count();

            if(check())
            {
              is_busy = false;
            }
        }
    }
      break;
  case(ActionIndex::message):
    {
      close_message_window();

      self.change_action_index(ActionIndex::null);

      is_busy = false;
    }
      break;
    }
}


void
render(EffectObject const&  self, Image&  dst, Point  offset) noexcept
{
  auto  rect = get_rectangle_for_item(thrown_item);

  offset += self.get_base_point();

  offset.transform(                        board_image_width,board_image_height);
  offset.transform(square_size,square_size,board_image_width,board_image_height);

  dst.transfer(character_image,rect,offset,self.get_base_point().y);
}


}


void
throw_item(GameItem const&  item, covered_ptr<Square>  start, Direction  d) noexcept
{
  thrown_item = item;

  current_square = start;

  event_queue::push(SquareEvent(SquareEventKind::flying_item_enter,start,nullptr,&thrown_item));

  moving_direction = d;

    if(check())
    {
      return;
    }


  Point  pt;

    switch(d)
    {
  case(Direction::front      ): pt = Point( 0, 1);break;
  case(Direction::front_left ): pt = Point(-1, 1);break;
  case(Direction::left       ): pt = Point(-1, 0);break;
  case(Direction::back_left  ): pt = Point(-1,-1);break;
  case(Direction::back       ): pt = Point( 0,-1);break;
  case(Direction::back_right ): pt = Point( 1,-1);break;
  case(Direction::right      ): pt = Point( 1, 0);break;
  case(Direction::front_right): pt = Point( 1, 1);break;
    }


  object.change_action_index(ActionIndex::moving);
  object.set_controll_callback(controll);
  object.set_render_callback(render);

  object.set_x_position(fixed_t(square_size*start->get_x()));
  object.set_y_position(fixed_t(square_size*start->get_y()));

  object.set_x_vector(fixed_t(pt.x*count_per_step));
  object.set_y_vector(fixed_t(pt.y*count_per_step));

  effect_director.insert_to_last(object);

  is_busy = true;
}


bool
is_thrown_item_busy() noexcept
{
  return is_busy;
}


}




