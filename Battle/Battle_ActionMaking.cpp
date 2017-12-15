#include"Battle.hpp"




namespace gmbb{


namespace{


void
render(Image&  dst, Point  pt, int  index)
{
  auto&  cmdtbl = get_current_player().get_command_table();

  dst.print(cmdtbl.commands[index].name.data(),pt,sys::glset);
}


ColumnStyleMenuWindow
menu_window(Menu(8*10,16,4,render),1,rect_of_versatile_window);


void
step() noexcept
{
    if(ctrl.is_p_button_pressing())
    {
      get_current_player().set_current_command(menu_window.get_item_index());

      auto&  cmd = get_current_player().get_current_command();

        if(cmd.effect_kind != EffectKind::null)
        {
          coprocesses::pop(1);
        }
    }

  else
    if(ctrl.is_n_button_pressing())
    {
      coprocesses::pop(0);
    }

  else
    if(sys::interval_timer.check(120,ctrl.get_time()))
    {
           if(ctrl.is_up_button_pressing()  ){menu_window.move_cursor_to_up();}
      else if(ctrl.is_down_button_pressing()){menu_window.move_cursor_to_down();}
    }
}


void
initialize() noexcept
{
  auto&  pl = get_current_player();

    if(pl.is_manual())
    {
      sys::root_task.push(menu_window);
    }

  else
    if(pl.is_automatic())
    {
      pl.set_current_command(0);

      coprocesses::pop();
    }
}


}


void
terminate_action_making() noexcept
{
  sys::root_task.erase(menu_window);
}


const coprocess
coprocess_of_action_making("action making",initialize,step);


}




