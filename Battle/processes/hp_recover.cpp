#include"Battle.hpp"




Process
hp_recover_process = [](Player&  actor, const BattleCommand&  command, Player&  target) noexcept
{
  auto&  cmd = actor.get_current_command();

  sys::push_text("%dHP　かいふくした",cmd.get_strength());
  gbstd::playworks::push(nullptr,playwork_of_stream_text);

  target.receive_hp_recover(cmd.get_strength());
};




