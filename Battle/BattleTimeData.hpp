#ifndef BattleTimeData_HPP
#define BattleTimeData_HPP


#include"BattlePlayer.hpp"


namespace gmbb{


extern Side    hero_side;
extern Side   enemy_side;

namespace tmp{
extern rw_ptr<Player>  player_pointer;
extern BattleAction    action        ;
}


void  clear_player_all() noexcept;


}




#endif




