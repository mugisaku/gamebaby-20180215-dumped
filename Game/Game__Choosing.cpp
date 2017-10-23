#include"Game_private.hpp"




namespace gmbb{


namespace{


ColumnStyleMenuWindow*
menu_window;


char const*
table[8];


bool
is_cancelable;


void
process(Controller const&  ctrl) noexcept
{
  using namespace gmbb::flags_of_input;

    if(ctrl.test(p_button))
    {
      pop_routine(menu_window->get_item_index());
    }

  else
    if(is_cancelable && ctrl.test(n_button))
    {
      pop_routine(-1);
    }

  else
    if(interval_timer.check(200,ctrl.get_time()))
    {
           if(ctrl.test(up_button)  ){  menu_window->move_cursor_to_up();  interval_timer.enable();}
      else if(ctrl.test(down_button)){  menu_window->move_cursor_to_down();  interval_timer.enable();}
      else {interval_timer.disable();}
    }
}


void
callback(Image&  dst, Point  point, int  i) noexcept
{
  dst.print(table[i],point,glset);
}


void
create_window() noexcept
{
    if(!menu_window)
    {
      Menu  menu(glset.get_width()*5,glset.get_height(),0,callback);

      menu_window = new ColumnStyleMenuWindow(menu,1,Point());

      menu_window->set_name("choosing menu window");
    }
}


}


void
prepare_choosing_window(std::initializer_list<char const*>  ls, Point  point) noexcept
{
  create_window();


  int  row_n = 0;

  auto  it = std::begin(table);

    for(auto&  s: ls)
    {
        if(s)
        {
          *it++ = s;

          ++row_n;
        }
    }


  menu_window->change_row_number(row_n);

  menu_window->set_base_point(point);
}


void
open_choosing_window() noexcept
{
  create_window();

  root_task.push(*menu_window);

  menu_window->set_state(WindowState::full_opened);
}


void
close_choosing_window() noexcept
{
    if(menu_window)
    {
      root_task.erase(*menu_window);

      menu_window->reset_cursor();
    }
}


void
start_choosing(bool  cancelable) noexcept
{
  open_choosing_window();

  is_cancelable = cancelable;

  push_routine(process);
}


}




