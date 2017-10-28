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
pickup_item_if_is(Piece&  actor) noexcept
{
  auto&  sq = *actor.get_square();

  auto&  i = sq.get_item();

    if(i)
    {
      actor.change_action_index(ActionIndex::message);

      char  buf[256] = {0};

      auto  pickedup = hero.get_sack().try_to_push_item(i);

      char const*  fmt = "%sを　ひろった";

      auto  name = i->get_name();

        if(!pickedup)
        {
          fmt = "%sがおちていたが　もちものがいっぱいで　ひろえない";
        }

      else
        {
          i = GameItem();
        }


      snprintf(buf,sizeof(buf),fmt,name);

      start_message(buf,nullptr);
    }
}


void
prepare_to_move(Piece&  p, Square&  sq, Direction  d) noexcept
{
    if(sq.get_piece())
    {
      event_queue::push(PieceEvent(PieceEventKind::push,&p,sq.get_piece()));

      return;
    }


    if(sq == SquareKind::wall)
    {
      event_queue::push(SquareEvent(SquareEventKind::piece_push,p.get_square(),&p,nullptr));

      return;
    }


  event_queue::push(SquareEvent(SquareEventKind::piece_leave,p.get_square(),&p,nullptr));
  event_queue::push(SquareEvent(SquareEventKind::piece_enter,           &sq,&p,nullptr));

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

  event_queue::push(PieceEvent(PieceEventKind::start_move,&p,nullptr));

  is_busy = true;
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

              event_queue::push(PieceEvent(PieceEventKind::end_move,&self,nullptr));

              pickup_item_if_is(self);

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

  event_queue::push(SquareEvent(SquareEventKind::piece_turn,hero_piece->get_square(),hero_piece,nullptr));
}


void
turn_hero_piece_to_right()
{
  hero_piece->turn_direction_to_right();

  event_queue::push(SquareEvent(SquareEventKind::piece_turn,hero_piece->get_square(),hero_piece,nullptr));
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




