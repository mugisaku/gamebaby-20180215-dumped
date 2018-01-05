#include"Battle.hpp"
#include<functional>




namespace gmbb{


std::vector<Process>
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




}




