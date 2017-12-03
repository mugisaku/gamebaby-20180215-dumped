#include"Battle.hpp"
#include<list>




namespace gmbb{


namespace{


FixedString
label("battle");


constexpr int  status_window_h = (16*3);


class
StatusWindow: public Window
{
  const int  index;

public:
  StatusWindow(int  i): Window(8*9,status_window_h,Point(216,status_window_h*i)), index(i){}

  void  render(Image&  dst, Point  offset) const noexcept override
  {
    Window::render(dst,offset);

    offset += get_base_point();

    offset.x += 8;
    offset.y += 8;

    StringBuffer  sbuf;


    auto  ch = sav::party.members[index];

      if(ch)
      {
        dst.print(ch->name.data(),offset,system_data::glset);
        dst.print(sbuf("HP %4d",ch->current_hp),offset.move_y(8),system_data::glset);
        dst.print(sbuf("MP %4d",ch->current_mp),offset.move_y(8),system_data::glset);
      }
  }

} status_windows[4] = {
    StatusWindow(0),
    StatusWindow(1),
    StatusWindow(2),
    StatusWindow(3)
  };


coreturn_t
ret_hunger;


std::list<Action>
action_list;


void  return_from_action_choosing(int  retval) noexcept;


void
return_from_action_processing(int  retval) noexcept
{
    if(action_list.size())
    {
      action = action_list.front();

      action_list.pop_front();

      start_action_processing(return_from_action_processing);
    }

  else
    {
      clear_stream_text();

      start_action_choosing(return_from_action_choosing,0);
    }
}


void
return_from_action_choosing(int  retval) noexcept
{
  terminate_action_choosing();

    if(retval == 0)
    {
      start_action_choosing(return_from_action_choosing,0);
    }

  else
    if(retval == 1)
    {
      action_list.emplace_back(action);

      action = action_list.front();

      action_list.pop_front();

      start_action_processing(return_from_action_processing);
    }
}


void
return_from_stream_text(int  retval) noexcept
{
  clear_stream_text();

  start_action_choosing(return_from_action_choosing,0);
}


}


void
terminate_battle() noexcept
{
    for(auto&  w: status_windows)
    {
      system_data::root_task.erase(w);
    }
}


void
start_battle(coreturn_t  ret) noexcept
{
  ret_hunger = ret;

  system_data::char_buffer.push("まものが　あらわれた");

  auto&  ene = enemy_player_table[0];

  ene.name = "おばけがえる";

  ene.body_strength = 30;
  ene.mind_strength =  0;
  ene.agility       =  7;
  ene.update();
  ene.replenish_hp();

    for(auto&  w: status_windows)
    {
      system_data::root_task.push(w);
    }


  start_stream_text(return_from_stream_text);
}


}




