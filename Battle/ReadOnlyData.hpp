#ifndef game_ReadOnlyData_HPP
#define game_ReadOnlyData_HPP


#include"BattlePlayerBase.hpp"
#include"BattleEnemy.hpp"
#include"BattleEnemyParty.hpp"
#include"libgbstd/entry_list.hpp"
#include<vector>


namespace ro{


extern const std::vector<PlayerBase>&
player_base_table;


extern const std::vector<Enemy>&
enemy_table;


extern const std::vector<EnemyParty>&
enemy_party_table;


const BattleCommand&  get_command(gbstd::string_view  name) noexcept;


void  load() noexcept;


}




#endif




