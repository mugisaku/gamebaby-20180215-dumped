#include"Battle.hpp"
#include<functional>




namespace gmbb{


std::vector<Process>
search_process_list(
{
[](Player&  actor, const BattleCommand&  command, Player&  target) noexcept
{
  sys::char_buffer.push(sbuf("%sは　%sを かんていした",actor.get_name().data(),target.get_name().data()));
  playworkes::push(nullptr,playwork_of_stream_text);
},
[](Player&  actor, const BattleCommand&  command, Player&  target) noexcept
{
  sys::char_buffer.push(sbuf("HP %4d/%4d",target.get_hp(),target.get_hp_max()));
  sys::char_buffer.push(sbuf("MP %4d/%4d",target.get_mp(),target.get_mp_max()));
  sys::char_buffer.push(sbuf("たいりょく %3d",target.get_body_strength()));
  sys::char_buffer.push(sbuf("せいしんりょく %3d",target.get_mind_strength()));
  sys::char_buffer.push(sbuf("すばやさ %3d",target.get_agility()));
  sys::char_buffer.push(sbuf("ちせい %3d",target.get_intellect()));
  sys::char_buffer.push(sbuf("しゅびりょく %3d",target.get_defense()));
  playworkes::push(nullptr,playwork_of_stream_text);
},
});




}




