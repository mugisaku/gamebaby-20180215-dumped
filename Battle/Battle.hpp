#ifndef game_Battle_HPP
#define game_Battle_HPP


#include"gmbb_Standard.hpp"
#include"SystemData.hpp"
#include"TemporaryData.hpp"
#include"ReadOnlyData.hpp"
#include"BattleTimeData.hpp"
#include"SavedData.hpp"
#include"Pointer.hpp"
#include<initializer_list>


namespace gmbb{


using Process = void  (*)(Player&  actor, const BattleCommand&  command, Player&  target) noexcept;


struct
ProcessList
{
  Process  m_begin;
  Process  m_end;

public:
  ProcessList(std::initializer_list<Process>  ls) noexcept:
  m_begin(*ls.begin()),
  m_end(*ls.end()){}

};


extern const Rectangle
rect_of_versatile_window;


void  clear_stream_text(               ) noexcept;
extern const coprocess  coprocess_of_stream_text;

void  set_parties_of_battle(const EnemyParty&  enep) noexcept;

extern const coprocess  coprocess_of_battle;


void  terminate_action_making() noexcept;

extern const coprocess  coprocess_of_action_making;


void  set_actor_of_action_processing(Player&  actor_) noexcept;

extern const coprocess  coprocess_of_action_processing;
 

}




#endif




