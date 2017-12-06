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

    for(int  n = 0;  n < action.actor->get_number_of_attacks();  ++n)
    {
        if(uni_dist(0,99) < 70)
        {
          ++res.hit_count;

          int  guard_point = 0;

            for(int  nn = 0;  nn < action.target->get_number_of_guards();  ++nn)
            {
                if(uni_dist(0,99) < 80)
                {
                  double  mean = action.target->get_guard_strength();
                  auto  stddev = mean/10;

                  guard_point += norm_dist(mean,stddev);
                }
            }


          auto  damage_point = action.actor->get_attack_strength();

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
      system_data::char_buffer.push(sbuf("%sは　%sに こうげき！",action.actor->get_name().data(),action.target->get_name().data()));
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
step_guard(const Controller&  ctrl) noexcept
{
    switch(phase_count)
    {
  case(0):
      system_data::char_buffer.push(sbuf("%sは　ぼうぎょを　かためた",action.actor->get_name().data()));
      start_stream_text(return_from_some_routine);
      break;
    }
}


void
step(const Controller&  ctrl) noexcept
{
    switch(action.kind)
    {
  case(ActionKind::attack):
      step_attack(ctrl);
      break;
  case(ActionKind::guard):
      step_guard(ctrl);
      break;
  case(ActionKind::null):
  default:
      pop_routine(label.pointer);
      break;
    }
}


}


void
start_action_processing(coreturn_t  ret) noexcept
{
    switch(action.kind)
    {
  case(ActionKind::null):
      phase_count = 0;
      break;
  case(ActionKind::attack):
      phase_count = 1;
      break;
  case(ActionKind::guard):
      phase_count = 0;
      break;
  default:
      printf("[start action processing error]\n");
    }


  push_routine(label.pointer,step,ret);
}


}




