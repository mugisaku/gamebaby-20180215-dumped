#ifndef game_SystemData_HPP
#define game_SystemData_HPP


#include"libgbstd/interval_timer.hpp"
#include"libgbstd/image.hpp"
#include"libgbstd/task.hpp"
#include"libgbstd/text.hpp"
#include"libgbstd/playwork.hpp"
#include"libgbstd/unicode.hpp"
#include"libgbstd/menu.hpp"
#include"libgbstd/controller.hpp"


namespace sys{




extern gbstd::interval_timer
interval_timer;


extern
gbstd::font
font;


extern
gbstd::font
large_font;


extern
gbstd::group_task
root_task;


extern gbstd::text_buffer
text_buffer;


void  push_text(const char*  fmt, ...) noexcept;


}




#endif




