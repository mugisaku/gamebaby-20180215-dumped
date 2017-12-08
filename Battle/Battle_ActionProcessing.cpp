#include"Battle.hpp"




namespace gmbb{


namespace{


FixedString
label("action processing");


int
phase_count;


StringBuffer
sbuf;


struct
ResultOfAttack
{
  int  damage_point=0;
  int     hit_count=0;

};


ResultOfAttack
get_result_of_attack() noexcept
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

            for(int  nn = 0;  nn < tmp::action.target->get_number_of_guards();  ++nn)
            {
                if(uni_dist(0,99) < 80)
                {
                  double  mean = tmp::action.target->get_guard_strength();
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
step_attack(const Controller&  ctrl) noexcept
{
    switch(phase_count)
    {
  case(1):
      system_data::char_buffer.push(sbuf("%sは　%sに こうげき！",tmp::player_pointer->get_name().data(),tmp::action.target->get_name().data()));
      start_stream_text(return_from_some_routine);
      break;
  case(0):
        {
          auto  res = get_result_of_attack();

          system_data::char_buffer.push(sbuf("%dかいヒット",res.hit_count));
          system_data::char_buffer.push(sbuf("%dダメージを　あたえた",res.damage_point));
          start_stream_text(return_from_some_routine);
        }

      break;
    }
}


void
step_guard_up(const Controller&  ctrl) noexcept
{
    switch(phase_count)
    {
  case(0):
      system_data::char_buffer.push(sbuf("%sは　ぼうぎょを　かためた",tmp::player_pointer->get_name().data()));
      start_stream_text(return_from_some_routine);
      break;
    }
}


void
step(const Controller&  ctrl) noexcept
{
    switch(tmp::action.command->effect_kind)
    {
  case(EffectKind::attack):
      step_attack(ctrl);
      break;
  case(EffectKind::guard_up):
      step_guard_up(ctrl);
      break;
  case(EffectKind::null):
  default:
      pop_routine(label.pointer);
      break;
    }
}


}


void
start_action_processing(coreturn_t  ret) noexcept
{
  auto  cmd = tmp::action.command;

    if(cmd)
    {
        switch(cmd->effect_kind)
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


}




