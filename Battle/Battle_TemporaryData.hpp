#ifndef Battle_TemporaryData_HPP
#define Battle_TemporaryData_HPP


#include"BattlePlayer.hpp"
#include"BattleAction.hpp"


namespace gmbb{


extern Side    hero_side;
extern Side   enemy_side;

extern rw_ptr<Player>  current_player;

extern Action  action;


void  clear_player_all() noexcept;


}




#endif




