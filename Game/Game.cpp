#include"Game_private.hpp"




namespace gmbb{


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
waiting(Controller const&  ctrl) noexcept
{
  using namespace gmbb::flags_of_input;

    if(is_main_menu_window_opened())
    {
      close_main_menu_window();

      hide_status_reportor();
    }


    if(is_message_window_opened())
    {
        if(ctrl.test(p_button))
        {
          close_message_window();

          wait_until_button_is_released();
        }


      return;
    }


  auto  ok = !is_hero_busy();

    if(ok && ctrl.test(p_button))
    {
    }

  else
    if(ok && ctrl.test(n_button))
    {
      open_main_menu_window();

      start_main_menu(nullptr);

      show_status_reportor();
    }

  else
    {
        if(ok && interval_timer.check(280,ctrl.get_time()))
        {
               if(ctrl.test(up_button   )){move_hero_piece_to_forward();  interval_timer.enable();}
          else if(ctrl.test(left_button )){turn_hero_piece_to_left( );  interval_timer.enable();}
          else if(ctrl.test(right_button)){turn_hero_piece_to_right();  interval_timer.enable();}
          else if(ctrl.test(down_button )){move_hero_piece_to_backward();  interval_timer.enable();}
          else {interval_timer.disable();}
        }
    }
}




Image const&
get_screen_image() noexcept
{
  return screen_image;
}


void
initialize() noexcept
{
#ifdef EMSCRIPTEN
        glset.load_from_file("small_font.bin");
  large_glset.load_from_file("large_font.bin");

  File  f("",File::get_content_from_file("image.png"));

  load_script_file("script.gamn");
#else
        glset.load_from_file("/usr/local/share/gmbb/small_font.bin");
  large_glset.load_from_file("/usr/local/share/gmbb/large_font.bin");

  File  f("",File::get_content_from_file("../bin/image.png"));

  load_script_file("../script.gamn");
#endif

  board.set_script_processor(process_script);


  auto  r = f.make_reader();

  character_image.load_png(r);


  root_task.push(board);
  board.push(effect_director);

  push_routine(waiting,nullptr);

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


  screen_image.fill();

  root_task.render(screen_image,Point());
}


}




