#include"Battle.hpp"




namespace gmbb{


namespace{


FixedString
label("action processing");


int
phase_count;


StringBuffer
sbuf;


random_number::Descriptor
desc;


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

  auto&   actor_cldat = tmp::action.actor->class_data;
  auto&  target_cldat = tmp::action.target->class_data;

    for(int  n = 0;  n < actor_cldat.number_of_attacks;  ++n)
    {
        if(1)
        {
          ++res.hit_count;

          int  guard_point = 0;

            for(int  nn = 0;  nn < target_cldat.number_of_guards;  ++nn)
            {
                if(1)
                {
                  guard_point += target_cldat.number_of_guards;
                }
            }


          auto  damage_point = actor_cldat.number_of_attacks;

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
      system_data::char_buffer.push(sbuf("%sは　%sに",tmp::action.actor->name,tmp::action.target->name));
      system_data::char_buffer.push(sbuf("こうげき！"));
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
      system_data::char_buffer.push(sbuf("%sは　ぼうぎょを　かためた",tmp::action.actor->name));
      start_stream_text(return_from_some_routine);
      break;
    }
}


void
step(const Controller&  ctrl) noexcept
{
    switch(tmp::action.kind)
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
    if(!desc)
    {
      desc = random_number::add_normal(0.0,80.0);
for(auto  n = 0;  n < 100;++n)
{
printf("%8d\n",(uint32_t)desc());
}


    }


    switch(tmp::action.kind)
    {
  case(ActionKind::null):
      phase_count = 0;
      break;
  case(ActionKind::attack):
      phase_count = 0;
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




