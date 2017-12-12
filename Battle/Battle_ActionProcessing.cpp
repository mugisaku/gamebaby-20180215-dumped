#include"Battle.hpp"
#include<functional>




namespace gmbb{


namespace{


FixedString
label("action processing");


struct
ResultOfAttack
{
  int  damage_point=0;
  int     hit_count=0;

};


ResultOfAttack
get_result_of_attack(Player&  target) noexcept
{
  ResultOfAttack  res;

  random_number::UniformDistribution  uni_dist;
  random_number::NormalDistribution  norm_dist;

    for(int  n = 0;  n < tmp::player_pointer->get_number_of_attacks();  ++n)
    {
        if(uni_dist(0,99) < 70)
        {
          ++res.hit_count;

          int  guard_point = 0;

            for(int  nn = 0;  nn < target.get_number_of_guards();  ++nn)
            {
                if(uni_dist(0,99) < 80)
                {
                  double  mean = target.get_guard_strength();
                  auto  stddev = mean/10;

                  guard_point += norm_dist(mean,stddev);
                }
            }


          auto  damage_point = tmp::player_pointer->get_attack_strength();

          res.damage_point += (damage_point > guard_point)? damage_point-guard_point:1;
        }
    }


  return res;
}




StringBuffer
sbuf;


BattleTeam::PlayerList
target_player_list;


BattleTeam::PlayerList::iterator  target_it    ;
BattleTeam::PlayerList::iterator  target_it_end;


using Process = void  (*)(Player&  target) noexcept;

std::vector<Process>
null_process_list;


std::vector<Process>
attack_process_list(
{
[](Player&  target)
{
  sys::char_buffer.push(sbuf("%sは　%sに こうげき！",tmp::player_pointer->get_name().data(),target.get_name().data()));
  start_stream_text(nullptr);
},
[](Player&  target)
{
  auto  res = get_result_of_attack(target);

  sys::char_buffer.push(sbuf("%dかいヒット",res.hit_count));
  sys::char_buffer.push(sbuf("%dダメージを　あたえた",res.damage_point));
  start_stream_text(nullptr);

  target.receive_hp_damage(res.damage_point);
},
});


std::vector<Process>
appraise_process_list(
{
[](Player&  target)
{
  sys::char_buffer.push(sbuf("%sは　%sを かんていした",tmp::player_pointer->get_name().data(),target.get_name().data()));
  start_stream_text(nullptr);
},
[](Player&  target)
{
  sys::char_buffer.push(sbuf("HP %4d/%4d",target.get_hp(),target.get_hp_max()));
  sys::char_buffer.push(sbuf("MP %4d/%4d",target.get_mp(),target.get_mp_max()));
  start_stream_text(nullptr);
},
});


std::vector<Process>::const_iterator  process_it    ;
std::vector<Process>::const_iterator  process_it_end;


std::reference_wrapper<std::vector<Process>>
process_list(null_process_list);


void
step_guard_up(Player&  target) noexcept
{
/*
     switch(phase_count)
    {
  case(0):
      sys::char_buffer.push(sbuf("%sは　ぼうぎょを　かためた",tmp::player_pointer->get_name().data()));
      start_stream_text(return_from_some_routine);
      break;
    }
*/
}


void
step(const Controller&  ctrl) noexcept
{
RESTART:
    if(process_it != process_it_end)
    {
      auto&  process = *process_it++;

        if(target_it != target_it_end)
        {
          process(**target_it);
        }

      else
        {
          goto QUIT;
        }
    }

  else
    if(target_it != target_it_end)
    {
      process_it     = process_list.get().cbegin();
      process_it_end = process_list.get().cend();

      ++target_it;

      goto RESTART;
    }


QUIT:
  pop_routine(label.pointer);
}


}


void
start_action_processing(coreturn_t  ret) noexcept
{
  auto&  curpl = *tmp::player_pointer;

  auto&  cmd = curpl.get_current_command();

  target_player_list.resize(0);

    switch(cmd.target_kind)
    {
  case(TargetKind::null):
      break;
  case(TargetKind::self):
      target_player_list.emplace_back(make_rw(curpl));
      break;
  case(TargetKind::one_of_own_team):
      target_player_list.emplace_back(curpl.get_own_team()->pickup_target_player());
      break;
  case(TargetKind::all_of_own_team):
      curpl.get_own_team()->collect_alive_players(target_player_list);
      break;
  case(TargetKind::one_of_opposite_team):
      target_player_list.emplace_back(curpl.get_opposite_team()->pickup_target_player());
      break;
  case(TargetKind::all_of_opposite_team):
      curpl.get_opposite_team()->collect_alive_players(target_player_list);
      break;
  case(TargetKind::all_of_both_team):
           curpl.get_own_team()->collect_alive_players(target_player_list);
      curpl.get_opposite_team()->collect_alive_players(target_player_list);
      break;
    }


  target_it     = target_player_list.begin();
  target_it_end = target_player_list.end();

    switch(cmd.effect_kind)
    {
  case(EffectKind::attack):
      process_list = std::ref(attack_process_list);
      break;
  case(EffectKind::guard_up):
      break;
  case(EffectKind::appraise):
      process_list = std::ref(appraise_process_list);
      break;
  case(EffectKind::null):
      process_list = std::ref(null_process_list);
      break;
    }


  process_it     = process_list.get().cbegin();
  process_it_end = process_list.get().cend();

  push_routine(label.pointer,step,ret);
}


}




