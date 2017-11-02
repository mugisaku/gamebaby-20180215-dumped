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
  Event  evt;

  auto  next = (*current_square)[moving_direction];

    if(next)
    {
        if(*next == SquareKind::wall)
        {
          board.clear_all_distance();

          current_square->put_item(thrown_item,3);

          effect_director.erase(object);


          evt.kind = EventKind::flying_item_Collide_with_wall;

          evt.flying_item.item   = &thrown_item;
          evt.flying_item.square = current_square;

          event_queue::push(evt);

          return true;
        }

      else
        if(next->get_piece())
        {
          auto  p = next->get_piece();


          evt.kind = EventKind::flying_item_Collide_with_piece;

          evt.flying_item.item  = &thrown_item;
          evt.flying_item.piece = p;

          event_queue::push(evt);

          effect_director.erase(object);

          return true;
        }

      else
        {
          evt.kind = EventKind::flying_item_Leave_from_square;

          evt.flying_item.item   = &thrown_item;
          evt.flying_item.square = current_square;

          event_queue::push(evt);


          evt.kind = EventKind::flying_item_Enter_into_square;
          evt.flying_item.square = next;

          event_queue::push(evt);

          current_square = next;
        }
    }

  else
    {
      evt.kind = EventKind::flying_item_Erase;

      evt.flying_item.item   = &thrown_item;
      evt.flying_item.square = next;

      event_queue::push(evt);

      effect_director.erase(object);

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


  Event  evt(EventKind::flying_item_Enter_into_square);

  evt.flying_item.item   = &thrown_item;
  evt.flying_item.square = start;

  event_queue::push(evt);

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

  effect_director.push(object);

  is_busy = true;
}


bool
is_thrown_item_busy() noexcept
{
  return is_busy;
}


}




