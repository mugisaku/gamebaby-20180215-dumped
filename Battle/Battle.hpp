#ifndef game_Battle_HPP
#define game_Battle_HPP


#include"gmbb_Standard.hpp"
#include"SystemData.hpp"
#include"TemporaryData.hpp"
#include"ReadOnlyData.hpp"
#include"Battle_TemporaryData.hpp"
#include"SavedData.hpp"
#include"Pointer.hpp"


namespace gmbb{


extern const Rectangle
rect_of_versatile_window;


void  clear_stream_text(               ) noexcept;
void  start_stream_text(coreturn_t  ret) noexcept;

void  start_battle(coreturn_t  ret) noexcept;

void  terminate_action_choosing() noexcept;
void  start_action_choosing(coreturn_t  ret, int  num) noexcept;

void  start_action_processing(coreturn_t  ret) noexcept;
 

}




#endif




