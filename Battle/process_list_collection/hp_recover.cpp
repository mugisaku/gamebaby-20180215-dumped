#include"Battle.hpp"
#include<functional>




namespace gmbb{


std::vector<Process>
hp_recover_process_list(
{
[](Player&  actor, const BattleCommand&  command, Player&  target) noexcept
{
  sys::char_buffer.push(sbuf("%sは　%sで",actor.get_name().data(),commnd.get_name().data()));
  sys::char_buffer.push(sbuf("%sに こうげき！",target.get_name().data()));
  coprocesses::push(nullptr,coprocess_of_stream_text);
},
[](Player&  actor, const BattleCommand&  command, Player&  target) noexcept
{
  target.receive_hp_recover(res.damage_point);

    if(!target.get_hp())
    {
      sys::char_buffer.push(sbuf("%sは　たおれた",target.get_name().data()));
    }
});




}




