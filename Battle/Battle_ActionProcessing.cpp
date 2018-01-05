#include"Battle.hpp"
#include<functional>




extern Process      attack_process;
extern Process         use_process;
extern Process   hp_damage_process;
extern Process  hp_recover_process;


namespace{


PlayerReference
actor;



BattleTeam::PlayerList
target_player_list;


BattleTeam::PlayerList::iterator  target_it    ;
BattleTeam::PlayerList::iterator  target_it_end;


Process  action_process;
Process  effect_process;


void
initialize() noexcept
{
  auto&  cmd = actor.get().get_current_command();

  target_player_list.resize(0);

    switch(cmd.get_target_kind())
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

    switch(cmd.get_action_kind())
    {
  case(ActionKind::attack): action_process = attack_process;break;
  case(ActionKind::use   ): action_process =    use_process;break;
  case(ActionKind::null):
      break;
    }


    switch(cmd.get_effect_kind())
    {
  case(EffectKind::hp_damage ): effect_process =  hp_damage_process;break;
  case(EffectKind::hp_recover): effect_process = hp_recover_process;break;
  case(EffectKind::null):
      break;
    }
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
        if(action_process)
        {
          auto&  pl = actor.get();

          action_process(pl,pl.get_current_command(),*target_it);
        }


      ++pc;
      break;
  case(3):
        if(effect_process)
        {
          auto&  pl = actor.get();

          effect_process(pl,pl.get_current_command(),*target_it);
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




