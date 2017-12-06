#include"BattlePlayerBase.hpp"


namespace gmbb{


void
PlayerBase::
load(const char*  name_, const gbdn::list&  ls) noexcept
{
  name = name_;
  body_strength = ls.get_named_value("body_strength").get_integer();
  mind_strength = ls.get_named_value("mind_strength").get_integer();
  agility       = ls.get_named_value("agility").get_integer();
  defense       = ls.get_named_value("defense").get_integer();
  intellect     = ls.get_named_value("intellect").get_integer();
  hp            = ls.get_named_value("hp").get_integer();
  mp            = ls.get_named_value("mp").get_integer();
}


}




