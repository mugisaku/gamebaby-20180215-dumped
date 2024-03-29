#ifndef BattleTimeData_HPP
#define BattleTimeData_HPP


#include"BattleTeam.hpp"


extern BattleTeam    hero_team;
extern BattleTeam   enemy_team;


Player&  get_current_player() noexcept;

void  rewind_player_iterator() noexcept;

bool     seek_first_actable_player() noexcept;
bool      seek_next_actable_player() noexcept;
bool  seek_previous_actable_player() noexcept;

void  collect_actable_player(std::vector<PlayerReference>&  buf) noexcept;

void   clear_player_all() noexcept;
void  update_player_all() noexcept;




#endif




