#ifndef GMBB_Game_private_HPP
#define GMBB_Game_private_HPP


#include"Game.hpp"
#include"Board.hpp"
#include"GameData.hpp"
#include"gmbb_Script.hpp"
#include<initializer_list>


namespace gmbb{


extern
Hero
hero;


extern
covered_ptr<Piece>
hero_piece;


extern
Board
board;


extern
Image
screen_image;


extern
Image
character_image;


extern IntervalTimer
interval_timer;


extern
GlyphSet
glset;


extern
GlyphSet
large_glset;


extern
GroupTask
root_task;


extern
Director
effect_director;


void  process_event() noexcept;




script::ListNode const*  find_routine(std::string const&  name) noexcept;
void  open_script(char const*  filepath) noexcept;


void  process_script(Director&  di, script::ListNode const*&  cur);


void  controll_hero_piece(Piece&  self) noexcept;
void    render_hero_piece(Piece const&  self, Image&  dst, Point  dst_point) noexcept;

void  throw_item(GameItem const&  item, covered_ptr<Square>  start, Direction  d) noexcept;

void  move_hero_piece_to_forward();
void  turn_hero_piece_to_left();
void  turn_hero_piece_to_right();
void  move_hero_piece_to_backward();

bool  is_hero_busy() noexcept;




void  show_status_monitor() noexcept;
void  hide_status_monitor() noexcept;

void  show_status_reportor() noexcept;
void  hide_status_reportor() noexcept;

void  show_debugger() noexcept;
void  hide_debugger() noexcept;


bool  is_status_monitor_window_opened() noexcept;
bool  is_status_report_window_opened()  noexcept;


void   open_main_menu_window() noexcept;
void  close_main_menu_window() noexcept;
void  start_main_menu() noexcept;
bool  is_main_menu_window_opened() noexcept;


void   open_sack_menu_window() noexcept;
void  close_sack_menu_window() noexcept;
void  start_sack_menu() noexcept;
bool  is_sack_menu_window_opened()      noexcept;


void  prepare_choosing_window(std::initializer_list<char const*>  ls, Point  point) noexcept;
void   open_choosing_window() noexcept;
void  close_choosing_window() noexcept;
void    start_choosing(bool  cancelable=true) noexcept;
bool  is_choosing_window_opened()       noexcept;


void   open_message_window() noexcept;
void  close_message_window() noexcept;
void  start_message(char const*  text, bool  cleaning=true) noexcept;
void  start_message_with_choosing(char const*  text, std::initializer_list<char const*>  ls, bool  cleaning=true) noexcept;
bool  is_message_window_opened()        noexcept;



}




#endif




