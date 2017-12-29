#include"Battle.hpp"
#include<list>




namespace gmbb{


namespace{


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


using List = std::vector<PlayerReference>;

List  actable_player_list;

List::iterator  actable_player_it    ;
List::iterator  actable_player_it_end;


void  return_from_action_making(int  retval) noexcept;


void
judge(uint32_t&  pc) noexcept
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
      pc = 5;

      clear_stream_text();

      sys::char_buffer.push("すべてのてきを　たおした");

      coprocesses::push(nullptr,coprocess_of_stream_text);
      break;
  case(hero_team_was_defeated_by_enemy_team):
  case(battle_was_a_draw):
      pc = 5;

      clear_stream_text();

      sys::char_buffer.push("ぜんめつした");

      coprocesses::push(nullptr,coprocess_of_stream_text);
      break;
  case(battle_is_continued):
      pc = 3;
      break;
    }
}


void
return_from_action_making(int  retval) noexcept
{
  terminate_action_making();

    if(retval == 0)
    {
        if(seek_previous_actable_player() ||
              seek_first_actable_player())
        {
          coprocesses::push(return_from_action_making,coprocess_of_action_making);
        }
    }

  else
    if(retval == 1)
    {
        if(seek_next_actable_player())
        {
          coprocesses::push(return_from_action_making,coprocess_of_action_making);
        }
    }
}


void
step(uint32_t&  pc) noexcept
{
    switch(pc)
    {
  case(0):
//coprocesses::debug(true);
        for(auto&  w: status_windows)
        {
          sys::root_task.push(w);
        }


      coprocesses::push(nullptr,coprocess_of_stream_text);
      ++pc;
      break;
  case(1):
      clear_stream_text();

        if(seek_first_actable_player())
        {
          coprocesses::push(return_from_action_making,coprocess_of_action_making);
        }

      ++pc;
      break;
  case(2):
      actable_player_list.resize(0);

      collect_actable_player(actable_player_list);

      actable_player_it     = actable_player_list.begin();
      actable_player_it_end = actable_player_list.end();

      ++pc;
  case(3):
        if(actable_player_it != actable_player_it_end)
        {
          set_actor_of_action_processing(actable_player_it++->get());

          coprocesses::push(nullptr,coprocess_of_action_processing);

          ++pc;
        }

      else
        {
          pc = 1;
        }
      break;
  case(4):
      judge(pc);
      break;
  case(5):
  default:
      coprocesses::pop();
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
set_parties_of_battle(const EnemyParty&  enep) noexcept
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

  StringBuffer  sbuf;

    for(auto  ene: enep.enemies)
    {
      e->set_operation_style(OperationStyle::automatic);

      sys::char_buffer.push(sbuf("%sが　あらわれた",ene->get_name().data()));

      e++->set_data(*ene);
    }
}


const coprocess
coprocess_of_battle("battle",step);


}




