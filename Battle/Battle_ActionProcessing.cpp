#include"Battle.hpp"
#include<list>




namespace gmbb{


namespace{


FixedString
label("action processing");


int
phase_count;


StringBuffer
sbuf;


std::list<std::reference_wrapper<Player>>
target_player_list;


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




void
return_from_some_routine(int  retval) noexcept
{
    if(!phase_count--)
    {
      pop_routine(label.pointer);
    }
}


void
step_attack(Player&  target) noexcept
{
    switch(phase_count)
    {
  case(1):
      sys::char_buffer.push(sbuf("%sは　%sに こうげき！",tmp::player_pointer->get_name().data(),target.get_name().data()));
      start_stream_text(return_from_some_routine);
      break;
  case(0):
        {
          auto  res = get_result_of_attack(target);

          sys::char_buffer.push(sbuf("%dかいヒット",res.hit_count));
          sys::char_buffer.push(sbuf("%dダメージを　あたえた",res.damage_point));
          start_stream_text(return_from_some_routine);
        }

      break;
    }
}


void
step_guard_up(Player&  target) noexcept
{
     switch(phase_count)
    {
  case(0):
      sys::char_buffer.push(sbuf("%sは　ぼうぎょを　かためた",tmp::player_pointer->get_name().data()));
      start_stream_text(return_from_some_routine);
      break;
    }
}


void
step(const Controller&  ctrl) noexcept
{
    if(target_player_list.size())
    {
      auto&  cmd = tmp::player_pointer->get_current_command();

      auto&  target = target_player_list.front().get();

      target_player_list.pop_front();

        switch(cmd.effect_kind)
        {
      case(EffectKind::attack):
          step_attack(target);
          break;
      case(EffectKind::guard_up):
          step_guard_up(target);
          break;
      case(EffectKind::null):
          break;
        }
    }


    if(target_player_list.empty())
    {
      pop_routine(label.pointer);
    }
}


}


void
start_action_processing(coreturn_t  ret) noexcept
{
  auto&  curpl = *tmp::player_pointer;

  auto&  cmd = curpl.get_current_command();

    switch(cmd.target_kind)
    {
  case(TargetKind::null):
      break;
  case(TargetKind::self):
      target_player_list.emplace_back(std::ref(curpl));
      break;
  case(TargetKind::one_of_own_team):
      target_player_list.emplace_back(std::ref(curpl));
      break;
  case(TargetKind::all_of_own_team):
        for(auto&  pl: *curpl.get_own_team())
        {
          target_player_list.emplace_back(std::ref(pl));
        }
      break;
  case(TargetKind::one_of_opposite_team):
      target_player_list.emplace_back(std::ref(curpl));
      break;
  case(TargetKind::all_of_opposite_team):
        for(auto&  pl: *curpl.get_opposite_team())
        {
          target_player_list.emplace_back(std::ref(pl));
        }
      break;
  case(TargetKind::all_of_both_team):
        for(auto&  pl: *curpl.get_own_team())
        {
          target_player_list.emplace_back(std::ref(pl));


        }
        for(auto&  pl: *curpl.get_opposite_team())
        {
          target_player_list.emplace_back(std::ref(pl));
        }
      break;
    }


    switch(cmd.effect_kind)
    {
  case(EffectKind::null):
      phase_count = 0;
      break;
  case(EffectKind::attack):
      phase_count = 1;
      break;
  default:
      printf("[start action processing error]\n");
    }


  push_routine(label.pointer,step,ret);
}


}




