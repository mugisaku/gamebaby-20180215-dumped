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


    auto  pl = hero_team[index];

      if(pl)
      {
        dst.print(pl.get_name().data(),offset,sys::glset);
        dst.print(sbuf("HP %4d",pl.get_hp()),offset.move_y(8),sys::glset);
        dst.print(sbuf("MP %4d",pl.get_mp()),offset.move_y(8),sys::glset);
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


using List = std::vector<reference_wrapper<Player>>;

List  actable_player_list;

List::iterator  actable_player_it    ;
List::iterator  actable_player_it_end;


void  return_from_action_making(int  retval) noexcept;


void
return_from_text_stream_when_hero_defeated_enemy(int  retval) noexcept
{
  pop_routine(label.pointer);
}


void
return_from_text_stream_when_hero_was_defeated_by_enemy(int  retval) noexcept
{
  pop_routine(label.pointer);
}


void
return_from_action_processing(int  retval) noexcept
{
  int  n  =  hero_team.can_continue_to_battle()? 1:0;
       n |= enemy_team.can_continue_to_battle()? 2:0;

  constexpr int  battle_was_a_draw                    = 0;
  constexpr int  hero_team_defeated_enemy_team        = 1;
  constexpr int  hero_team_was_defeated_by_enemy_team = 2;
  constexpr int  battle_is_continued                  = 3;

    switch(n)
    {
  case(hero_team_defeated_enemy_team):
      clear_stream_text();

      sys::char_buffer.push("てきを　しりぞけた");

      start_stream_text(return_from_text_stream_when_hero_defeated_enemy);
      break;
  case(hero_team_was_defeated_by_enemy_team):
  case(battle_was_a_draw):
      clear_stream_text();

      sys::char_buffer.push("てきに　やぶれた");

      start_stream_text(return_from_text_stream_when_hero_was_defeated_by_enemy);
      break;
  case(battle_is_continued):
        if(actable_player_it != actable_player_it_end)
        {
          start_action_processing(return_from_action_processing,actable_player_it++->get());
        }

      else
        {
          clear_stream_text();

          rewind_player_iterator();

          start_action_making(return_from_action_making);
        }
      break;
    }
}


void
return_from_action_making(int  retval) noexcept
{
  terminate_action_making();

    if(retval == 0)
    {
        if(seek_previous_actable_player())
        {
          start_action_making(return_from_action_making);
        }
    }

  else
    if(retval == 1)
    {
        if(seek_next_actable_player())
        {
          start_action_making(return_from_action_making);
        }

      else
        {
          actable_player_list.resize(0);

          collect_actable_player(actable_player_list);

          actable_player_it     = actable_player_list.begin();
          actable_player_it_end = actable_player_list.end();

            if(actable_player_it != actable_player_it_end)
            {
              start_action_processing(return_from_action_processing,actable_player_it++->get());
            }

          else
            {
              return_from_action_processing(0);
            }
        }
    }
}


void
return_from_stream_text(int  retval) noexcept
{
  clear_stream_text();

    if(seek_next_actable_player())
    {
      start_action_making(return_from_action_making);
    }

  else
    {
      return_from_action_making(1);
    }
}


}


void
terminate_battle() noexcept
{
    for(auto&  w: status_windows)
    {
      sys::root_task.erase(w);
    }
}


void
start_battle(coreturn_t  ret, const EnemyParty&  enep) noexcept
{
  clear_player_all();

  auto  pl = hero_team.begin();

    for(auto  m: sav::party.members)
    {
        if(m)
        {
          pl->set_data(*m);
        }


      ++pl;
    }


  auto  e = enemy_team.begin();

    for(auto  ene: enep.enemies)
    {
      e->set_operation_style(OperationStyle::automatic);

      e++->set_data(*ene);
    }


  ret_hunger = ret;

  sys::char_buffer.push("まものが　あらわれた");

    for(auto&  w: status_windows)
    {
      sys::root_task.push(w);
    }


  rewind_player_iterator();

  start_stream_text(return_from_stream_text);
}


}




