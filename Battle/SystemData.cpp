#include"SystemData.hpp"


namespace sys{


gbstd::group_task
root_task;


gbstd::interval_timer
interval_timer;


gbstd::font
font;


gbstd::font
large_font;


gbstd::text_buffer
text_buffer(1024);


void
push_text(const char*  fmt, ...) noexcept
{
  va_list  ap;
  va_start(ap,fmt);

  text_buffer.push(gbstd::make_text_with_va_list(fmt,ap));

  va_end(ap);
}


}




