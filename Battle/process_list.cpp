#include"Battle.hpp"




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
        if(uni_dist(0,99) < 90)
        {
          ++res.hit_count;

          int  guard_point = 0;

            for(int  nn = 0;  nn < target.get_number_of_guards();  ++nn)
            {
                if(uni_dist(0,99) < 60)
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
process_list = {
{"hp_damage",[](Player&  actor, const BattleCommand&  command, Player&  target) noexcept
{
  auto  res = get_result_of_attack(actor,target);

  sys::push_text("%dかいヒット",res.hit_count);
  sys::push_text("%dダメージを　あたえた",res.damage_point);
  gbstd::playworks::push(nullptr,playwork_of_stream_text);

  target.receive_hp_damage(res.damage_point);

    if(!target.get_hp())
    {
      sys::push_text("%sは　たおれた",target.get_name().data());
    }
}},



{"attack",[](Player&  actor, const BattleCommand&  command, Player&  target) noexcept
{
  sys::push_text("%sは　%sで",actor.get_name().data(),command.get_name().data());
  sys::push_text("%sに こうげき！",target.get_name().data());
  gbstd::playworks::push(nullptr,playwork_of_stream_text);
}},


{"hp_recover",[](Player&  actor, const BattleCommand&  command, Player&  target) noexcept
{
  int  v = command.get_strength();

  sys::push_text("%dHP　かいふくした",v);
  gbstd::playworks::push(nullptr,playwork_of_stream_text);

  target.receive_hp_recover(v);
}},


{"drink_ordinary_water",[](Player&  actor, const BattleCommand&  command, Player&  target) noexcept
{
  sys::push_text("ごくごくごく・・・");
  sys::push_text("%sは　のどの　かわきが　いやされた",target.get_name().data());
  sys::push_text("しかし　からだの　きずは　いえなかった");

  gbstd::playworks::push(nullptr,playwork_of_stream_text);
}},


{"use",[](Player&  actor, const BattleCommand&  command, Player&  target) noexcept
{
  sys::push_text("%sは　%sを",actor.get_name().data(),command.get_name().data());
  sys::push_text("%sに つかった！",target.get_name().data());
  gbstd::playworks::push(nullptr,playwork_of_stream_text);
}},
};




/*Process
search_process_list(
{
[](Player&  actor, const BattleCommand&  command, Player&  target) noexcept
{
  sys::push_text("%sは　%sを かんていした",actor.get_name().data(),target.get_name().data());
  playworkes::push(nullptr,playwork_of_stream_text);
},
[](Player&  actor, const BattleCommand&  command, Player&  target) noexcept
{
  sys::push_text("HP %4d/%4d",target.get_hp(),target.get_hp_max());
  sys::push_text("MP %4d/%4d",target.get_mp(),target.get_mp_max());
  sys::push_text("たいりょく %3d",target.get_body_strength());
  sys::push_text("せいしんりょく %3d",target.get_mind_strength());
  sys::push_text("すばやさ %3d",target.get_agility());
  sys::push_text("ちせい %3d",target.get_intellect());
  sys::push_text("しゅびりょく %3d",target.get_defense());
  playworkes::push(nullptr,playwork_of_stream_text);
},
});
*/




