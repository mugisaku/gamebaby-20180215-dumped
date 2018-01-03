#include"Battle.hpp"
#include<functional>




extern std::initializer_list<Process>  attack_process_list;


namespace{


PlayerReference
actor;



BattleTeam::PlayerList
target_player_list;


BattleTeam::PlayerList::iterator  target_it    ;
BattleTeam::PlayerList::iterator  target_it_end;


using Process = void  (*)(Player&  actor, const BattleCommand&  command, Player&  target) noexcept;


std::initializer_list<Process>*  process_list;

std::initializer_list<Process>::const_iterator  process_it    ;
std::initializer_list<Process>::const_iterator  process_it_end;


void
set_list(std::initializer_list<Process>&  ls)
{
  process_list = &ls;
}


void
initialize() noexcept
{
  auto&  cmd = actor.get().get_current_command();

  target_player_list.resize(0);

    switch(cmd.target_kind)
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

    switch(cmd.effect_kind)
    {
  case(EffectKind::attack):
      set_list(attack_process_list);
      break;
  case(EffectKind::hp_recover):
//      process_list = std::ref(hp_recover_process_list);
      break;
  case(EffectKind::null):
//      process_list = std::ref(null_process_list);
      break;
    }


  process_it     = process_list->begin();
  process_it_end = process_list->end();
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
        if(process_it != process_it_end)
        {
          auto&  process = *process_it++;

            if(target_it != target_it_end)
            {
              auto&  pl = actor.get();

              process(pl,pl.get_current_command(),*target_it);
            }

          else
            {
              ++pc;
            }
         }

      else
        if(target_it != target_it_end)
        {
          process_it     = process_list->begin();
          process_it_end = process_list->end();

          ++target_it;

          clear_stream_text();
        }

      else
        {
          ++pc;
        }
      break;
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




