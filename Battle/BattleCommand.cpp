#include"BattleCommand.hpp"


namespace gmbb{


namespace{
EffectKind
to_effect(const gbdn::string&  s) noexcept
{
       if(s == gbdn::string_view("null"  )){return EffectKind::null;}
  else if(s == gbdn::string_view("attack")){return EffectKind::attack;}
  else if(s == gbdn::string_view("appraise")){return EffectKind::appraise;}

  return EffectKind::null;
}


TargetKind
to_target(const gbdn::string&  s) noexcept
{
       if(s == gbdn::string_view("null"                )){return TargetKind::null;}
  else if(s == gbdn::string_view("self"                )){return TargetKind::self;}
  else if(s == gbdn::string_view("one_of_own_team"     )){return TargetKind::one_of_own_team;}
  else if(s == gbdn::string_view("all_of_own_team"     )){return TargetKind::all_of_own_team;}
  else if(s == gbdn::string_view("one_of_opposite_team")){return TargetKind::one_of_opposite_team;}
  else if(s == gbdn::string_view("all_of_opposite_team")){return TargetKind::all_of_opposite_team;}
  else if(s == gbdn::string_view("all_of_both_team"    )){return TargetKind::all_of_both_team;}

  return TargetKind::null;
}


}


void
BattleCommand::
load(const char*  name_, const gbdn::list&  ls)
{
  name = name_;

  strength = ls.get_named_value("strength").get_integer();
  weight   = ls.get_named_value("weight").get_integer();

  effect_kind = to_effect(ls.get_named_value("effect").get_string());
  target_kind = to_target(ls.get_named_value("target").get_string());
}


}




