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
return_from_text_stream_when_hero_defeated_enemy(int  retval) noexcept
{
  coprocesses::pop();
}


void
return_from_text_stream_when_hero_was_defeated_by_enemy(int  retval) noexcept
{
  coprocesses::pop();
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

      coprocesses::push(return_from_text_stream_when_hero_defeated_enemy,coprocess_of_stream_text);
      break;
  case(hero_team_was_defeated_by_enemy_team):
  case(battle_was_a_draw):
      clear_stream_text();

      sys::char_buffer.push("てきに　やぶれた");

      coprocesses::push(return_from_text_stream_when_hero_was_defeated_by_enemy,coprocess_of_stream_text);
      break;
  case(battle_is_continued):
        if(actable_player_it != actable_player_it_end)
        {
          coprocesses::push(return_from_action_processing,coprocess_of_action_processing);
//          start_action_processing(return_from_action_processing,actable_player_it++->get());
        }

      else
        {
          clear_stream_text();

          seek_first_actable_player();

          coprocesses::push(return_from_action_making,coprocess_of_action_making);
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

      else
        {
          actable_player_list.resize(0);

          collect_actable_player(actable_player_list);

          actable_player_it     = actable_player_list.begin();
          actable_player_it_end = actable_player_list.end();

            if(actable_player_it != actable_player_it_end)
            {
//              start_action_processing(return_from_action_processing,actable_player_it++->get());
              coprocesses::push(return_from_action_processing,coprocess_of_action_processing);
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

    if(seek_first_actable_player())
    {
      coprocesses::push(return_from_action_making,coprocess_of_action_making);
    }

  else
    {
      return_from_action_making(1);
    }
}


void
initialize() noexcept
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


/*
  auto  e = enemy_team.begin();

  StringBuffer  sbuf;

    for(auto  ene: enep.enemies)
    {
      e->set_operation_style(OperationStyle::automatic);

      sys::char_buffer.push(sbuf("%sが　あらわれた",ene->get_name().data()));

      e++->set_data(*ene);
    }
*/

    for(auto&  w: status_windows)
    {
      sys::root_task.push(w);
    }


  coprocesses::push(return_from_stream_text,coprocess_of_stream_text);
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


const coprocess
coprocess_of_battle("battle",initialize,nullptr);


}




