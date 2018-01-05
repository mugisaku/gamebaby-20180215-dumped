#include"Battle.hpp"
#include<functional>




Process
use_process = [](Player&  actor, const BattleCommand&  command, Player&  target) noexcept
{
  sys::push_text("%sは　%sを",actor.get_name().data(),command.get_name().data());
  sys::push_text("%sに つかった！",target.get_name().data());
  gbstd::playworks::push(nullptr,playwork_of_stream_text);
};




