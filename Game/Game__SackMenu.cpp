#include"Game_private.hpp"




namespace gmbb{


namespace{


ColumnStyleMenuWindow*
menu_window;


covered_ptr<GameItem>
item_ptr;


void
callback(Image&  dst, Point  point, int  i)
{
  auto&  gi = hero.get_sack().get_item(i);

    if(gi)
    {
        if(gi.is_equipped())
        {
          dst.print(u'E',point,glset);
        }


      point.x += glset.get_width();

        if(gi.is_cursed())
        {
          dst.print(u'C',point,glset);
        }


      point.x += glset.get_width();

      dst.print(gi->get_name(),point,glset);
    }
}


void
return_(int  retval) noexcept
{
  constexpr int  top    = 0;
  constexpr int  throw_ = 1;
  constexpr int  put    = 2;

    if(retval >= 0)
    {
        switch(retval)
        {
      case(top):
          hero_piece->hold_item(item_ptr);
          break;
      case(throw_):
          hero_piece->unhold_item(item_ptr);

          throw_item(*item_ptr,hero_piece->get_square(),hero_piece->get_direction());

          *item_ptr = GameItem();

          pop_routine(-1);
          break;
      case(put):
          auto&  sq = *hero_piece->get_square();

            if(sq.can_put_item())
            {
              hero_piece->unhold_item(item_ptr);

              sq.set_item(*item_ptr);

              *item_ptr = GameItem();

              pop_routine(-1);
            }

          else
            {
            }

          break;
        }


      hero.get_sack().sort();
    }


  close_choosing_window();
}


void
process(Controller const&  ctrl) noexcept
{
  using namespace gmbb::flags_of_input;

    if(ctrl.test(p_button))
    {
      auto&  gi = hero.get_sack().get_item(menu_window->get_item_index());

        if(gi)
        {
          item_ptr = &gi;

          char const*  fon = gi->get_first_operation_name();


          prepare_choosing_window({fon,"なげる",hero_piece->get_square()->can_put_item()? "おく":nullptr},Point(40,80));

          start_choosing(true,return_);
        }
    }

  else
    if(ctrl.test(n_button))
    {
      pop_routine();
    }

  else
    if(interval_timer.check(200,ctrl.get_time()))
    {
           if(ctrl.test(up_button)   ){menu_window->move_cursor_to_up();  interval_timer.enable();}
      else if(ctrl.test(down_button) ){menu_window->move_cursor_to_down();  interval_timer.enable();}
      else if(ctrl.test(left_button) ){menu_window->move_cursor_to_left();  interval_timer.enable();}
      else if(ctrl.test(right_button)){menu_window->move_cursor_to_right();  interval_timer.enable();}
      else {interval_timer.disable();}
    }
}


}


void
open_sack_menu_window() noexcept
{
    if(!menu_window)
    {
      Menu  menu(glset.get_width()*20,glset.get_height(),8,callback);

      menu_window = new ColumnStyleMenuWindow(menu,2,Point(96,24));

      menu_window->set_name("sack menu window");
    }



  root_task.push(*menu_window);

  menu_window->set_state(WindowState::full_opened);
}


void
close_sack_menu_window() noexcept
{
    if(menu_window)
    {
      menu_window->reset_cursor();

      root_task.erase(*menu_window);

      menu_window->set_state(WindowState::hidden);
    }
}


void
start_sack_menu(Return  retcb) noexcept
{
  open_sack_menu_window();

  hero.get_sack().sort();

  push_routine(process,retcb);
}


}




