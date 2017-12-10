#ifndef BattleTimeData_HPP
#define BattleTimeData_HPP


#include"BattleTeam.hpp"


namespace gmbb{


extern BattleTeam    hero_team;
extern BattleTeam   enemy_team;

namespace tmp{
extern rw_ptr<Player>  player_pointer;
}


void  clear_player_all() noexcept;


}




#endif




