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


    auto  pl = hero_side.players[index];

      if(pl)
      {
        dst.print(pl.get_name().data(),offset,system_data::glset);
        dst.print(sbuf("HP %4d",pl.get_hp()),offset.move_y(8),system_data::glset);
        dst.print(sbuf("MP %4d",pl.get_mp()),offset.move_y(8),system_data::glset);
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


std::list<rw_ptr<Player>>
player_list;


void  return_from_action_making(int  retval) noexcept;


void
prepare_to_start_action_processing() noexcept
{
  tmp::player_pointer = player_list.front();

  tmp::action = tmp::player_pointer->get_action();

  player_list.pop_front();
}


void
return_from_action_processing(int  retval) noexcept
{
    if(player_list.size())
    {
      prepare_to_start_action_processing();

      start_action_processing(return_from_action_processing);
    }

  else
    {
      clear_stream_text();

      tmp::player_pointer = make_rw(hero_side.players[0]);

      start_action_making(return_from_action_making);
    }
}


void
return_from_action_making(int  retval) noexcept
{
  terminate_action_making();

    if(retval == 0)
    {
      auto  begin = &hero_side.players[0];

        if(tmp::player_pointer > begin)
        {
          --tmp::player_pointer;
        }


      start_action_making(return_from_action_making);
    }

  else
    if(retval == 1)
    {
      auto  end = &hero_side.players[Side::number_of_players];

      tmp::player_pointer->set_action(tmp::action);

      player_list.emplace_back(tmp::player_pointer++);

REDO:
        if(tmp::player_pointer >= end)
        {
          prepare_to_start_action_processing();

          start_action_processing(return_from_action_processing);
        }

      else
        if(tmp::player_pointer->is_actable())
        {
          start_action_making(return_from_action_making);
        }

      else
        {
          ++tmp::player_pointer;

          goto REDO;
        }
    }
}


void
return_from_stream_text(int  retval) noexcept
{
  clear_stream_text();

  tmp::player_pointer = make_rw(hero_side.players[0]);

  start_action_making(return_from_action_making);
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
  clear_player_all();

  auto  pl = make_rw(hero_side.players[0]);

    for(auto  m: sav::party.members)
    {
        if(m)
        {
          pl->set_data(*m);
        }


      ++pl;
    }


  ret_hunger = ret;

  system_data::char_buffer.push("まものが　あらわれた");

    for(auto&  w: status_windows)
    {
      system_data::root_task.push(w);
    }


  start_stream_text(return_from_stream_text);
}


}




