#include"BattleCommand.hpp"




namespace{
EffectKind
to_effect(const gbdn::string&  s) noexcept
{
       if(s == std::string_view("null"  )){return EffectKind::null;}
  else if(s == std::string_view("hp_damage")){return EffectKind::hp_damage;}
  else if(s == std::string_view("hp_recover")){return EffectKind::hp_recover;}

  return EffectKind::null;
}


ActionKind
to_action(const gbdn::string&  s) noexcept
{
       if(s == std::string_view("null"  )){return ActionKind::null;}
  else if(s == std::string_view("attack")){return ActionKind::attack;}
  else if(s == std::string_view("use")){return ActionKind::use;}

  return ActionKind::null;
}


TargetKind
to_target(const gbdn::string&  s) noexcept
{
       if(s == std::string_view("null"                )){return TargetKind::null;}
  else if(s == std::string_view("self"                )){return TargetKind::self;}
  else if(s == std::string_view("one_of_own_team"     )){return TargetKind::one_of_own_team;}
  else if(s == std::string_view("all_of_own_team"     )){return TargetKind::all_of_own_team;}
  else if(s == std::string_view("one_of_opposite_team")){return TargetKind::one_of_opposite_team;}
  else if(s == std::string_view("all_of_opposite_team")){return TargetKind::all_of_opposite_team;}
  else if(s == std::string_view("all_of_both_team"    )){return TargetKind::all_of_both_team;}

  return TargetKind::null;
}


}


void
BattleCommand::
load(std::string_view  name, const gbdn::list&  ls)
{
  m_name = name;

  m_strength = ls.get_named_value("strength").get_integer();
  m_weight   = ls.get_named_value("weight").get_integer();

  m_effect_kind = to_effect(ls.get_named_value("effect").get_string());
  m_action_kind = to_action(ls.get_named_value("action").get_string());
  m_target_kind = to_target(ls.get_named_value("target").get_string());
}




