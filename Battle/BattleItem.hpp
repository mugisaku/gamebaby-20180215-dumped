#ifndef BattleItem_HPP
#define BattleItem_HPP


#include"BattlePlayerBase.hpp"


namespace gmbb{


enum class
BattleItemKind
{
  null,
  command,
  accessory,
  special_ability,
  empty,

};


enum class
TargetKind
{
  null,
  self,
  one,
  all_of_heroes_side,
  all_of_enemies_side,

};


enum class
EffectKind
{
  null,
  attack,
  guard_up,

};


struct
BattleCommand
{
  std::string  name;

  int  strength;
  int    weight;

  TargetKind  target_kind=TargetKind::null;
  EffectKind  effect_kind=EffectKind::null;

};


enum class
AbilityKind
{
  null,
  
};


struct
Accessory
{
  std::string  name;

  int  weight;

  AbilityKind  ability0_kind=AbilityKind::null;
  AbilityKind  ability1_kind=AbilityKind::null;

};


}




#endif




