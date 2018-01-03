#ifndef BattleEnemyParty_HPP
#define BattleEnemyParty_HPP


#include"BattleEnemy.hpp"
#include<vector>


struct
EnemyParty
{
  std::string  m_name;

  std::vector<gbstd::ro_ptr<Enemy>>  m_enemies;

  EnemyParty() noexcept{}
  EnemyParty(std::string_view  name, const gbdn::list&  ls){load(name,ls);}

  void  load(std::string_view  name, const gbdn::list&  ls);

};




#endif




