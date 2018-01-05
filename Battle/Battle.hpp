#ifndef game_Battle_HPP
#define game_Battle_HPP


#include"libgbstd/image.hpp"
#include"libgbstd/random_number.hpp"
#include"SystemData.hpp"
#include"TemporaryData.hpp"
#include"ReadOnlyData.hpp"
#include"BattleTimeData.hpp"
#include"SavedData.hpp"
#include<initializer_list>


using Process = void  (*)(Player&  actor, const BattleCommand&  command, Player&  target) noexcept;


extern const gbstd::rectangle
rect_of_versatile_window;


void  clear_stream_text() noexcept;
extern const gbstd::playwork  playwork_of_stream_text;

void  set_parties_of_battle(const EnemyParty&  enep) noexcept;

extern const gbstd::playwork  playwork_of_battle;


void  terminate_action_making() noexcept;

extern const gbstd::playwork  playwork_of_action_making;


void  set_actor_of_action_processing(Player&  actor_) noexcept;

extern const gbstd::playwork  playwork_of_action_processing;




#endif




