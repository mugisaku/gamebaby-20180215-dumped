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


void
prepare_to_move(Piece&  p, Square&  sq, Direction  d) noexcept
{
  Event  evt;

    if(sq.get_piece())
    {
      evt.kind = EventKind::piece_Push_piece;

      evt.piece.piece         = &p;
      evt.piece.another_piece = sq.get_piece();

      event_queue::push(evt);

      return;
    }


    if(sq == SquareKind::wall)
    {
      evt.kind = EventKind::piece_Push_wall;

      evt.piece.piece  = &p;
      evt.piece.square = &sq;

      event_queue::push(evt);

      return;
    }


    {
      evt.kind = EventKind::piece_Leave_from_square;

      evt.piece.piece  = &p;
      evt.piece.square = p.get_square();

      event_queue::push(evt);
    }


    {
      evt.kind = EventKind::piece_Enter_into_square;

      evt.piece.piece  = &p;
      evt.piece.square = &sq;

      event_queue::push(evt);
    }


  p.get_square()->set_piece(nullptr);

  sq.set_piece(&p);
  p.set_square(&sq);

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


  p.change_action_index(ActionIndex::moving);

  p.set_x_vector(fixed_t(pt.x)*2);
  p.set_y_vector(fixed_t(pt.y)*2);


  evt.kind = EventKind::piece_Start_move;

  evt.piece.piece = &p;
  
  event_queue::push(evt);

  is_busy = true;
}


}


void
pick_up_item_on_square(Piece&  actor) noexcept
{
  auto&  sq = *actor.get_square();

  auto&  i = sq.get_item();

    if(i)
    {
      actor.change_action_index(ActionIndex::message);

      auto  pickedup = hero.get_sack().try_to_push_item(i);

      clear_message_window();

        if(!pickedup)
        {
          start_message("when_has_no_empty",nullptr);
        }

      else
        {
          environment::set_value("item_on_square",i->get_name());

          start_message("picked_up_item_on_square",nullptr);

          i = GameItem();
        }

    }
}


void
controll_hero_piece(Piece&  self) noexcept
{
    switch(self.get_action_index())
    {
  case(ActionIndex::null):
      break;
  case(ActionIndex::moving):
    {
      board.move_view_point(*self.get_x_vector(),
                            *self.get_y_vector());

        if(self.get_frame_count() >= 3)
        {
          self.add_motion_count(1);

            if(self.get_motion_count() >= 4)
            {
              self.set_x_vector(fixed_t());
              self.set_y_vector(fixed_t());


              Event  evt(EventKind::piece_End_move);

              evt.piece.piece = hero_piece;
              
              event_queue::push(evt);

              pick_up_item_on_square(self);

              self.change_action_index(ActionIndex::null);

              is_busy = false;
            }

          else
            {
              self.reset_frame_count();
              self.seek_pattern_index(1);

                if(self.get_pattern_index() >= 4)
                {
                  self.set_pattern_index(0);
                }
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
move_hero_piece_to_forward()
{
  auto  sq = hero_piece->get_square();

  auto  d = hero_piece->get_direction();

  auto  dst = (*sq)[d];

    if(dst)
    {
      prepare_to_move(*hero_piece,*dst,d);
    }
}


void
turn_hero_piece_to_left()
{
  hero_piece->turn_direction_to_left();


  Event  evt(EventKind::piece_Turn);

  evt.piece.piece  = hero_piece;
  evt.piece.square = hero_piece->get_square();
  
  event_queue::push(evt);
}


void
turn_hero_piece_to_right()
{
  hero_piece->turn_direction_to_right();


  Event  evt(EventKind::piece_Turn);

  evt.piece.piece  = hero_piece;
  evt.piece.square = hero_piece->get_square();
  
  event_queue::push(evt);
}


void
move_hero_piece_to_backward()
{
  auto  sq = hero_piece->get_square();

  auto  d = get_opposite(hero_piece->get_direction());

  auto  dst = (*sq)[d];

    if(dst)
    {
      prepare_to_move(*hero_piece,*dst,d);
    }
}


bool
is_hero_busy() noexcept
{
  return is_busy;
}




void
render_hero_piece(Piece const&  p, Image&  dst, Point  offset) noexcept
{
  constexpr int  u = square_size;

  int  x;
  int  y;

  int  w = u  ;
  int  h = u*2;

    switch(p.get_direction())
    {
  case(Direction::front):
      y = 0;
      break;
  case(Direction::front_left ):
      y = h*3;
      break;
  case(Direction::left       ):
      y = h*1;
      break;
  case(Direction::back_left  ):
      y = h*4;
      break;
  case(Direction::back       ):
      y = h*2;
      break;
  case(Direction::back_right ):
      y = h*4;
      w = -w;
      break;
  case(Direction::right      ):
      y = h*1;
      w = -w;
      break;
  case(Direction::front_right):
      y = h*3;
      w = -w;
    }


  static int const  table[] = {0,1,0,2};

  x = u*table[p.get_pattern_index()];


  auto  pt = p.get_base_point()+offset;

  pt.y -= u;

  pt.transform(    board_image_width,board_image_height);
  pt.transform(w,h,board_image_width,board_image_height);


  Rectangle  rect(x,y,w,h);

  dst.transfer(character_image,rect,pt,p.get_base_point().y+80);
}


}




