#include"BattleCommand.hpp"


namespace gmbb{


namespace{
EffectKind
to_effect(const gbdn::string&  s) noexcept
{
       if(s == gbdn::string_view("null"  )){return EffectKind::null;}
  else if(s == gbdn::string_view("attack")){return EffectKind::attack;}

  return EffectKind::null;
}


TargetKind
to_target(const gbdn::string&  s) noexcept
{
       if(s == gbdn::string_view("null"                )){return TargetKind::null;}
  else if(s == gbdn::string_view("self"                )){return TargetKind::self;}
  else if(s == gbdn::string_view("one_of_own_side"     )){return TargetKind::one_of_own_side;}
  else if(s == gbdn::string_view("all_of_own_side"     )){return TargetKind::all_of_own_side;}
  else if(s == gbdn::string_view("one_of_opposite_side")){return TargetKind::one_of_opposite_side;}
  else if(s == gbdn::string_view("all_of_opposite_side")){return TargetKind::all_of_opposite_side;}
  else if(s == gbdn::string_view("all_of_both_side"    )){return TargetKind::all_of_both_side;}

  return TargetKind::null;
}


}


void
BattleCommand::
load(const char*  name_, const gbdn::list&  ls) noexcept
{
  name = name_;
  strength = ls.get_named_value("strength").get_integer();

  effect_kind = to_effect(ls.get_named_value("effect").get_string());
  target_kind = to_target(ls.get_named_value("target").get_string());
}


}




