#include"Battle.hpp"




namespace{


void
render(gbstd::image&  dst, gbstd::point  pt, int  index)
{
  auto&  cmdtbl = get_current_player().get_command_table();

  dst.print(cmdtbl.commands[index].get_name(),pt,sys::font);
}


gbstd::column_menu
menu_window(
  gbstd::menu_base(gbstd::menu_item_renderer(8*10,16,render),4),
  1,rect_of_versatile_window
);


void
step(uint32_t&  pc) noexcept
{
    if(!pc)
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

          gbstd::playworks::pop(1);
        }


      ++pc;
    }


    if(gbstd::ctrl.is_p_button_pressing())
    {
      get_current_player().set_current_command(menu_window.get_item_index());

      auto&  cmd = get_current_player().get_current_command();

        if(cmd.get_effect_kind() != EffectKind::null)
        {
          gbstd::playworks::pop(1);
        }
    }

  else
    if(gbstd::ctrl.is_n_button_pressing())
    {
      gbstd::playworks::pop(0);
    }

  else
    if(sys::interval_timer.check(120,gbstd::ctrl.get_time()))
    {
           if(gbstd::ctrl.is_up_button_pressing()  ){menu_window.move_cursor_to_up();}
      else if(gbstd::ctrl.is_down_button_pressing()){menu_window.move_cursor_to_down();}
    }
}


}


void
terminate_action_making() noexcept
{
  sys::root_task.erase(menu_window);

  menu_window.reset_cursor();
}


const gbstd::playwork
playwork_of_action_making("action making",step);




