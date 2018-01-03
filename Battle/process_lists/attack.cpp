#include"Battle.hpp"
#include<functional>




namespace{
struct
ResultOfAttack
{
  int  damage_point=0;
  int     hit_count=0;

};


ResultOfAttack
get_result_of_attack(Player&  actor, Player&  target) noexcept
{
  ResultOfAttack  res;

  gbstd::random_number::uniform_distribution  uni_dist;
  gbstd::random_number::normal_distribution  norm_dist;

    for(int  n = 0;  n < actor.get_number_of_attacks();  ++n)
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


          auto  damage_point = actor.get_attack_strength();

          res.damage_point += (damage_point > guard_point)? damage_point-guard_point:1;
        }
    }


  return res;
}


}


std::initializer_list<Process>
attack_process_list =
{
[](Player&  actor, const BattleCommand&  command, Player&  target) noexcept
{
  sys::text_buffer.push(gbstd::make_text("%sは　%sで",actor.get_name().data(),command.get_name().data()));
  sys::text_buffer.push(gbstd::make_text("%sに こうげき！",target.get_name().data()));
  gbstd::playworks::push(nullptr,playwork_of_stream_text);
},
[](Player&  actor, const BattleCommand&  command, Player&  target) noexcept
{
  auto  res = get_result_of_attack(actor,target);

  sys::text_buffer.push(gbstd::make_text("%dかいヒット",res.hit_count));
  sys::text_buffer.push(gbstd::make_text("%dダメージを　あたえた",res.damage_point));
  gbstd::playworks::push(nullptr,playwork_of_stream_text);

  target.receive_hp_damage(res.damage_point);

    if(!target.get_hp())
    {
      sys::text_buffer.push(gbstd::make_text("%sは　たおれた",target.get_name().data()));
    }
},
};




