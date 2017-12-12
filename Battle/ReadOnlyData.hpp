#ifndef game_ReadOnlyData_HPP
#define game_ReadOnlyData_HPP


#include"BattlePlayerBase.hpp"
#include"BattleEnemy.hpp"
#include"BattleEnemyParty.hpp"
#include<vector>


namespace gmbb{
namespace ro{


extern const std::vector<PlayerBase>&
player_base_table;


extern const std::vector<Enemy>&
enemy_table;


extern const std::vector<EnemyParty>&
enemy_party_table;


extern const std::vector<BattleCommand>&
command_table;


void  load() noexcept;


}}




#endif




