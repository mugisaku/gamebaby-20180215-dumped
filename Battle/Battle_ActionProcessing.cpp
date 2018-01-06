#include"Battle.hpp"
#include<functional>




namespace{


PlayerReference
actor;



BattleTeam::PlayerList
target_player_list;


BattleTeam::PlayerList::iterator  target_it    ;
BattleTeam::PlayerList::iterator  target_it_end;


const BattleCommand*
command;


void
initialize() noexcept
{
  command = actor.get().get_current_command();

  target_player_list.resize(0);

    switch(command->get_target_kind())
    {
  case(TargetKind::null):
      break;
  case(TargetKind::self):
      target_player_list.emplace_back(actor);
      break;
  case(TargetKind::one_of_own_team):
      target_player_list.emplace_back(*actor.get().get_own_team()->pickup_target_player());
      break;
  case(TargetKind::all_of_own_team):
      actor.get().get_own_team()->collect_alive_players(target_player_list);
      break;
  case(TargetKind::one_of_opposite_team):
      target_player_list.emplace_back(*actor.get().get_opposite_team()->pickup_target_player());
      break;
  case(TargetKind::all_of_opposite_team):
      actor.get().get_opposite_team()->collect_alive_players(target_player_list);
      break;
  case(TargetKind::all_of_both_team):
           actor.get().get_own_team()->collect_alive_players(target_player_list);
      actor.get().get_opposite_team()->collect_alive_players(target_player_list);
      break;
    }


  target_it     = target_player_list.begin();
  target_it_end = target_player_list.end();
}


void
step(uint32_t&  pc) noexcept
{
    switch(pc)
    {
  case(0):
      initialize();
      ++pc;
  case(1):
        if(target_it == target_it_end)
        {
          pc = 4;
        }

      else
        {
          clear_stream_text();

          ++pc;
        }
      break;
  case(2):
        if(auto  proc = command->get_action_process();  proc)
        {
          auto&  pl = actor.get();

          proc->callback(pl,*command,*target_it);
        }


      ++pc;
      break;
  case(3):
        if(auto  proc = command->get_effect_process();  proc)
        {
          auto&  pl = actor.get();

          proc->callback(pl,*command,*target_it);
        }


      ++target_it;

      pc = 1;
      break;
  case(4):
  default:;
      gbstd::playworks::pop();
    }
}


}


void
set_actor_of_action_processing(Player&  actor_) noexcept
{
  actor = actor_;
}


const gbstd::playwork
playwork_of_action_processing("action processing",step);




