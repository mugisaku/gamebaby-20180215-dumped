#include"Battle.hpp"




namespace gmbb{


namespace{


FixedString
label("action choosing");


void
render(Image&  dst, Point  pt, int  index)
{
  auto&  cmdtbl = tmp::player_pointer->get_command_table();

  dst.print(cmdtbl.commands[index].name.data(),pt,sys::glset);
}


ColumnStyleMenuWindow
menu_window(Menu(8*10,16,4,render),1,rect_of_versatile_window);


void
step(const Controller&  ctrl) noexcept
{
    if(ctrl.is_p_button_pressing())
    {
      tmp::player_pointer->set_current_command(menu_window.get_item_index());

      auto&  cmd = tmp::player_pointer->get_current_command();

        if(cmd.effect_kind != EffectKind::null)
        {
          pop_routine(label.pointer,1);
        }
    }

  else
    if(ctrl.is_n_button_pressing())
    {
      pop_routine(label.pointer,0);
    }

  else
    if(sys::interval_timer.check(120,ctrl.get_time()))
    {
           if(ctrl.is_up_button_pressing()  ){menu_window.move_cursor_to_up();}
      else if(ctrl.is_down_button_pressing()){menu_window.move_cursor_to_down();}
    }
}


}


void
terminate_action_making() noexcept
{
  sys::root_task.erase(menu_window);
}


void
start_action_making(coreturn_t  ret) noexcept
{
  sys::root_task.push(menu_window);

  push_routine(label.pointer,step,ret);
}


}




