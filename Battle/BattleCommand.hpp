#ifndef BattleCommand_HPP
#define BattleCommand_HPP


#include"libgbdn/gbdn.hpp"
#include<string>


enum class
TargetKind
{
  null,
  self,
  one_of_own_team,
  all_of_own_team,
  one_of_opposite_team,
  all_of_opposite_team,
  all_of_both_team,

};


enum class
EffectKind
{
  null,
  attack,
  hp_recover,

};


enum class
AbilityKind
{
  null,
  
};


struct
BattleCommand
{
  std::string  name;

  int  strength;
  int    weight;

  TargetKind  target_kind=TargetKind::null;
  EffectKind  effect_kind=EffectKind::null;

  BattleCommand() noexcept{}
  BattleCommand(const char*  name_, const gbdn::list&  ls){load(name_,ls);}

  const std::string&  get_name() const noexcept{return name;}

  void  load(const char*  name_, const gbdn::list&  ls);

};


struct
CommandTable
{
  static constexpr int  number_of_commands = 4;

  BattleCommand  commands[number_of_commands];

};




#endif




