#include"Game_private.hpp"




namespace gmbb{


bool  screen_modify;
bool  screen_reverse;

int  screen_r;
int  screen_g;
int  screen_b;


Hero
hero;


Board
board;


GroupTask
root_task;


Director
effect_director;


covered_ptr<Piece>
hero_piece;


IntervalTimer
interval_timer;


Image
screen_image(screen_width,screen_height);


GlyphSet
glset;


GlyphSet
large_glset;




void
return_(int  retval) noexcept
{
  close_sack_menu_window();
  close_main_menu_window();

  hide_status_reportor();
}


void
waiting(Controller const&  ctrl) noexcept
{
    if(is_message_window_opened())
    {
        if(is_message_window_clean())
        {
          close_message_window();
        }

      else
        if(ctrl.is_p_button_pressing())
        {
          close_message_window();

          wait_until_button_is_released();
        }


      return;
    }


  auto  ok = !is_hero_busy();

    if(ok && ctrl.is_p_button_pressing())
    {
    }

  else
    if(ok && ctrl.is_n_button_pressing())
    {
      open_main_menu_window();

      start_main_menu(return_);

      show_status_reportor();
    }

  else
    {
        if(ok && interval_timer.check(280,ctrl.get_time()))
        {
               if(   ctrl.is_up_button_pressing()){move_hero_piece_to_forward();  interval_timer.enable();}
          else if( ctrl.is_left_button_pressing()){turn_hero_piece_to_left( );  interval_timer.enable();}
          else if(ctrl.is_right_button_pressing()){turn_hero_piece_to_right();  interval_timer.enable();}
          else if( ctrl.is_down_button_pressing()){move_hero_piece_to_backward();  interval_timer.enable();}
          else {interval_timer.disable();}
        }
    }
}




Image const&
update_screen() noexcept
{
  screen_image.fill();

  root_task.render(screen_image,Point());

    if(screen_modify)
    {
      screen_image.add(screen_r,
                       screen_g,
                       screen_b);

        if(screen_reverse)
        {
          screen_image.reverse_color();
        }
    }


  return screen_image;
}


void
initialize() noexcept
{
  Stream  image_s;

#ifdef EMSCRIPTEN
        glset.load_from_file("small_font.gz");
  large_glset.load_from_file("large_font.gz");

  image_s.set_content_from_file("image.png");

  load_script_file("script.gamn");
#else
        glset.load_from_file("/usr/local/share/gmbb/small_font.gz");
  large_glset.load_from_file("/usr/local/share/gmbb/large_font.gz");

  image_s.set_content_from_file("../bin/image.png");

  load_script_file("../script.gamn");
#endif

  board.set_script_processor(process_script);


  auto  r = image_s.make_reader();

  character_image.load_png(r);


  root_task.push(board);
  board.push(effect_director);

//  push_routine(waiting,nullptr);
  push_routine(close_game,nullptr);

  show_status_monitor();
//  show_debugger();

    for(int  x = 0;  x < board_width;  ++x)
    {
      board.get_square(x,             0).set_kind(SquareKind::wall);
      board.get_square(x,board_height-1).set_kind(SquareKind::wall);
    }


    for(int  y = 1;  y < board_height-1;  ++y)
    {
      board.get_square(            0,y).set_kind(SquareKind::wall);
      board.get_square(board_width-1,y).set_kind(SquareKind::wall);
    }


    for(int  y = 1;  y < board_height-1;  ++y){
    for(int  x = 1;  x < board_width -1;  ++x){
      board.get_square(x,y).set_kind(SquareKind::room);
    }}


  board.set_script(find_script("routine","test")->get_list().get_first());

  reset_shops();
}


void
step(Controller const&  ctrl)
{
  process_event();

  root_task.update();

  call_routine(ctrl);
}


}




