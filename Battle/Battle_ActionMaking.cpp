#include"Battle.hpp"




namespace gmbb{


namespace{


FixedString
label("action choosing");


void
render(Image&  dst, Point  pt, int  index)
{
  auto&  cmdtbl = tmp::player_pointer->get_command_table();

  dst.print(cmdtbl.commands[index].name.data(),pt,system_data::glset);
}


ColumnStyleMenuWindow
menu_window(Menu(8*10,16,4,render),1,rect_of_versatile_window);


void
step(const Controller&  ctrl) noexcept
{
    if(ctrl.is_p_button_pressing())
    {
      auto&  table = tmp::player_pointer->get_command_table();

      auto  i = menu_window.get_item_index();

      tmp::action.command = &table.commands[i];

        if(i == 0)
        {
          tmp::action.target  = nullptr;
        }

      else
        if(i == 1)
        {
          tmp::action.target  = nullptr;
        }


      pop_routine(label.pointer,1);
    }

  else
    if(ctrl.is_n_button_pressing())
    {
      pop_routine(label.pointer,0);
    }

  else
    if(system_data::interval_timer.check(120,ctrl.get_time()))
    {
           if(ctrl.is_up_button_pressing()  ){menu_window.move_cursor_to_up();}
      else if(ctrl.is_down_button_pressing()){menu_window.move_cursor_to_down();}
    }
}


}


void
terminate_action_making() noexcept
{
  system_data::root_task.erase(menu_window);
}


void
start_action_making(coreturn_t  ret) noexcept
{
  tmp::action.command = nullptr;
  tmp::action.target  = nullptr;

  system_data::root_task.push(menu_window);

  push_routine(label.pointer,step,ret);
}


}




