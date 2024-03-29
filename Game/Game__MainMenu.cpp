#include"Game_private.hpp"
#include"EventQueue.hpp"




namespace gmbb{


namespace{


constexpr int        talk = 0;
constexpr int  belongings = 1;
constexpr int        foot = 2;
constexpr int   interrupt = 3;


ScrollStyleMenuWindow*
menu_window;


void
return_for_talk_command(int  retval) noexcept
{
  pop_routine();
}


void
return_for_foot_command(int  retval) noexcept
{
  pop_routine();
}


void
return_for_belongings_command(int  retval) noexcept
{
    if(retval == 0)
    {
      auto&  sq = *hero_piece->get_square();

      auto&  item = sq.get_item();
      auto&  trap = sq.get_trap();

        if(item)
        {
          pop_routine();
        }

      else
        if(trap)
        {
          pop_routine();
        }
    }


  close_sack_menu_window();
  close_message_window();
}


covered_ptr<Piece>
get_talk_target() noexcept
{
  auto  sq = hero_piece->get_square();

  auto  target_sq = sq->get_linked_square(hero_piece->get_direction());

  return target_sq? target_sq->get_piece():nullptr;
}


void
process(Controller const&  ctrl) noexcept
{
    if(ctrl.is_p_button_pressing())
    {
     clear_message_window();

        switch(menu_window->get_item_index())
        {
      case(talk):
          {
            auto  target = get_talk_target();

            clear_message_window();

              if(target)
              {
                auto&  role = target->get_role();

                auto  tka = role.find_talk_action(hero_piece->get_name());

                  if(tka)
                  {
                    Event  evt(EventKind::piece_Talk);

                    evt.piece.piece         = hero_piece;
                    evt.piece.another_piece = target;

                    event_queue::push(evt);


                    evt.piece.another_piece->change_direction(get_opposite(evt.piece.piece->get_direction()));

                    start_message(tka->label.data(),return_for_talk_command);
                  }

                else
                  {
                    start_message("no_data_for_talk",return_for_talk_command);
                  }
              }

            else
              {
                start_message("there_is_no_one_on_its_direction",return_for_talk_command);
              }


            hide_status_reportor();
          }
          break;
      case(belongings):
          start_sack_menu(return_for_belongings_command);
          break;
      case(foot):
        {
          auto&  sq = *hero_piece->get_square();

          auto&  item = sq.get_item();
          auto&  trap = sq.get_trap();

            if(item)
            {
              auto  empty = hero.get_sack().find_empty();

                if(empty)
                {
                  environment::set_value("item_on_square",(*item).get_name());

                  pickup_parameter.dst = empty;
                  pickup_parameter.src = &item;

                  start_message("whether_hero_picks_up_item",return_for_foot_command);
                }

              else
                {
                  start_message("when_has_no_empty",return_for_foot_command);
                }
            }

          else
            if(trap)
            {
              auto  empty = hero.get_sack().find_empty();

                if(empty)
                {
                  start_message("",return_for_foot_command);
                }

              else
                {
                  start_message("",return_for_foot_command);
                }
            }

          else
            {
              start_message("when_square_has_no_item",return_for_foot_command);
            }
        }
          break;
      case(interrupt):
          break;
      default:;
          break;
        }
    }

  else
    if(ctrl.is_n_button_pressing())
    {
      pop_routine();
    }

  else if(ctrl.is_up_button_pressing()   ){menu_window->move_cursor_to_up();}
  else if(ctrl.is_down_button_pressing() ){menu_window->move_cursor_to_down();}
  else if(ctrl.is_left_button_pressing() ){menu_window->move_cursor_to_left();}
  else if(ctrl.is_right_button_pressing()){menu_window->move_cursor_to_right();}
}


}


void
open_main_menu_window() noexcept
{
    if(!menu_window)
    {
      Menu  menu(glset.get_width()*5,glset.get_height(),2,[](Image&  dst, Point  point, int  i)
        {
          static char16_t const*  text_table[] = {
            u"はなす",u"もちもの",
            u"あしもと",u"",
          };


          dst.print(text_table[i],point,glset);
        });


      menu_window = new ScrollStyleMenuWindow(menu,2,2,Point(8,24));

      menu_window->set_name("main menu window");
    }


  root_task.push(*menu_window);

  menu_window->set_state(WindowState::full_opened);
}


void
close_main_menu_window() noexcept
{
  menu_window->reset_cursor();

  root_task.erase(*menu_window);
}


bool
is_main_menu_window_opened() noexcept
{
  return menu_window && menu_window->get_group();
}


void
start_main_menu(Return  retcb) noexcept
{
  open_main_menu_window();

  push_routine(process,retcb);
}


}




