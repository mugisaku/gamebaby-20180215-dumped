#ifndef BattleEnemyParty_HPP
#define BattleEnemyParty_HPP


#include"BattleEnemy.hpp"
#include<vector>


namespace gmbb{


struct
EnemyParty
{
  std::string  name;

  std::vector<ro_ptr<Enemy>>  enemies;

  EnemyParty() noexcept{}
  EnemyParty(const char*  name_, const gbdn::list&  ls){load(name_,ls);}

  void  load(const char*  name_, const gbdn::list&  ls);

};


}




#endif




