#ifndef BattleAction_HPP
#define BattleAction_HPP


#include"BattlePlayer.hpp"


namespace gmbb{


enum class
ActionKind
{
  null,
  attack,
  guard,

};


struct
Action
{
  ActionKind  kind;

  rw_ptr<Player>   actor;
  rw_ptr<Player>  target;

  TargetKind  target_kind;

};


}




#endif




