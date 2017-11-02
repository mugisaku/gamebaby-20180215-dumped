#include"Game_private.hpp"
#include"EventQueue.hpp"
#include"Shop.hpp"




namespace gmbb{


namespace{


ColumnStyleMenuWindow*
menu_window;


void
callback(Image&  dst, Point  point, int  i)
{
    if(i < shop::get_number_of_commodities())
    {
      auto&  comm = shop::get_commodity(i);

      char  buf[256];

      snprintf(buf,sizeof(buf),"%8d",comm.price.value);

      dst.print(comm.name.data(),point,glset);

      dst.print(buf,point+Point(glset.get_width()*12,0),glset);
    }
}


void
return_(int  retval) noexcept
{
    if(retval >= 0)
    {
    }
}


void
process(Controller const&  ctrl) noexcept
{
  using namespace gmbb::flags_of_input;

    if(ctrl.test(p_button))
    {
      auto&  comm = shop::get_commodity(menu_window->get_item_index());

      Event  evt(EventKind::shop_Buy_item);

      evt.shop.commodity = &comm;

      event_queue::push(evt);


      pop_routine(menu_window->get_item_index());
    }

  else
    if(ctrl.test(n_button))
    {
      Event  evt(EventKind::shop_Exit);

      event_queue::push(evt);


      pop_routine();
    }

  else
    if(interval_timer.check(200,ctrl.get_time()))
    {
           if(ctrl.test(up_button)   ){menu_window->move_cursor_to_up();  interval_timer.enable();}
      else if(ctrl.test(down_button) ){menu_window->move_cursor_to_down();  interval_timer.enable();}
//      else if(ctrl.test(left_button) ){menu_window->move_cursor_to_left();  interval_timer.enable();}
//      else if(ctrl.test(right_button)){menu_window->move_cursor_to_right();  interval_timer.enable();}
      else {interval_timer.disable();}
    }
}


}


void
open_shop_menu_window() noexcept
{
    if(!menu_window)
    {
      Menu  menu(glset.get_width()*20,glset.get_height(),8,callback);

      menu_window = new ColumnStyleMenuWindow(menu,2,Point(96,24));

      menu_window->set_name("shop menu window");
    }



  root_task.push(*menu_window);

  menu_window->set_state(WindowState::full_opened);
}


void
close_shop_menu_window() noexcept
{
  menu_window->reset_cursor();

  root_task.erase(*menu_window);

  menu_window->set_state(WindowState::hidden);
}


void
start_shop_menu(Return  retcb) noexcept
{
  Event  evt(EventKind::shop_Enter);

  event_queue::push(evt);

  open_shop_menu_window();

  push_routine(process,retcb);
}


}




