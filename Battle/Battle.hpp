#ifndef game_Battle_HPP
#define game_Battle_HPP


#include"gmbb_Standard.hpp"
#include"SystemData.hpp"
#include"TemporaryData.hpp"
#include"ReadOnlyData.hpp"
#include"BattleTimeData.hpp"
#include"SavedData.hpp"
#include"Pointer.hpp"


namespace gmbb{


extern const Rectangle
rect_of_versatile_window;


void  clear_stream_text(               ) noexcept;
extern const coprocess  coprocess_of_stream_text;

extern const coprocess  coprocess_of_battle;


void  terminate_action_making() noexcept;
extern const coprocess  coprocess_of_action_making;


extern const coprocess  coprocess_of_action_processing;
 

}




#endif




