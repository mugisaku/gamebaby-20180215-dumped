#include"Battle.hpp"




namespace gmbb{


namespace{


FixedString
label("action choosing");


const char*
actions[] =
{
  "こうげき",
  "ぼうぎょ",

};


void
render(Image&  dst, Point  pt, int  index)
{
  dst.print(actions[index],pt,system_data::glset);
}


ColumnStyleMenuWindow
menu_window(Menu(8*5,16,2,render),1,rect_of_versatile_window);


void
step(const Controller&  ctrl) noexcept
{
    if(ctrl.is_p_button_pressing())
    {
      auto  i = menu_window.get_item_index();

        if(i == 0)
        {
          action.actor       = &hero_side.players[0];
          action.target      = &enemy_side.players[0];
          action.target_kind = TargetKind::one_of_opposite_side;
          action.kind        = ActionKind::attack;
        }

      else
        if(i == 1)
        {
          action.actor       = &hero_side.players[0];
          action.target      = nullptr;
          action.target_kind = TargetKind::null;
          action.kind        = ActionKind::guard;
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
terminate_action_choosing() noexcept
{
  system_data::root_task.erase(menu_window);
}


void
start_action_choosing(coreturn_t  ret, int  num) noexcept
{
  action.actor       = nullptr;
  action.target      = nullptr;
  action.target_kind = TargetKind::null;
  action.kind        = ActionKind::null;

  system_data::root_task.push(menu_window);

  push_routine(label.pointer,step,ret);
}


}




