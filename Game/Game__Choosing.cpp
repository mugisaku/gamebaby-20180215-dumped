#include"Game_private.hpp"




namespace gmbb{


namespace{


ColumnStyleMenuWindow*
menu_window;


int
answer_length_max;


char const*
table[8];


char const**
pointer;


bool
is_cancelable;


void
process(Controller const&  ctrl) noexcept
{
    if(ctrl.is_p_button_pressing())
    {
      pop_routine(menu_window->get_item_index());
    }

  else
    if(is_cancelable && ctrl.is_n_button_pressing())
    {
      pop_routine(-1);
    }

  else
    if(interval_timer.check(200,ctrl.get_time()))
    {
           if(ctrl.is_up_button_pressing()  ){  menu_window->move_cursor_to_up();  interval_timer.enable();}
      else if(ctrl.is_down_button_pressing()){  menu_window->move_cursor_to_down();  interval_timer.enable();}
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
prepare_choosing_window(Point  point) noexcept
{
  create_window();

  pointer = table;

  answer_length_max = 0;

  menu_window->set_base_point(point);
}


void
append_answer(char const*  text) noexcept
{
    if(text)
    {
      *pointer++ = text;

      answer_length_max = std::max(answer_length_max,(int)u8slen(text));
    }
}


void
open_choosing_window() noexcept
{
  create_window();

  root_task.push(*menu_window);

  menu_window->change_item_width(answer_length_max);

  menu_window->change_row_number(pointer-table);

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
start_choosing(Avoidable  avo, Return  retcb) noexcept
{
  open_choosing_window();

  is_cancelable = avo.value;

  push_routine(process,retcb);
}


}




