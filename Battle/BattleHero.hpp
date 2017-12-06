#ifndef BattleHero_HPP
#define BattleHero_HPP


#include"BattlePlayerBase.hpp"


namespace gmbb{


struct
ExperienceSet
{
  uint32_t  attack=0;
  uint32_t   guard=0;
  uint32_t   magic=0;
  uint32_t  damage=0;

};


struct
Hero: public PlayerBase
{
  std::string  class_name;

  int  current_hp=0;
  int  current_mp=0;

  ExperienceSet  expset;

};


}




#endif




