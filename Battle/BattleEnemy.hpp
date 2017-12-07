#ifndef BattleEnemy_HPP
#define BattleEnemy_HPP


#include"BattlePlayerBase.hpp"


namespace gmbb{


struct
Enemy: public PlayerBase
{
  Enemy() noexcept{}
  Enemy(const char*  name_, const gbdn::list&  ls){load(name_,ls);}

  void  load(const char*  name_, const gbdn::list&  ls);

};


}




#endif




