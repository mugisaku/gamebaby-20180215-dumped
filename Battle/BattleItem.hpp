#ifndef BattleItem_HPP
#define BattleItem_HPP


#include"BattleCommand.hpp"




enum class
BattleItemKind
{
  null,
  command,
  accessory,
  special_ability,
  empty,

};


struct
Accessory
{
  std::string  name;

  int  weight;

  AbilityKind  ability0_kind=AbilityKind::null;
  AbilityKind  ability1_kind=AbilityKind::null;

};




#endif




