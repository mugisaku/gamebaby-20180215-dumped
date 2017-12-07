#ifndef BattleCommand_HPP
#define BattleCommand_HPP


#include"gbdn.hpp"
#include<string>


namespace gmbb{


enum class
TargetKind
{
  null,
  self,
  one_of_own_side,
  all_of_own_side,
  one_of_opposite_side,
  all_of_opposite_side,
  all_of_both_side,

};


enum class
EffectKind
{
  null,
  attack,
  guard_up,

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

  void  load(const char*  name_, const gbdn::list&  ls);

};


struct
CommandTable
{
  static constexpr int  number_of_commands = 4;

  BattleCommand  commands[number_of_commands];

};


}




#endif




