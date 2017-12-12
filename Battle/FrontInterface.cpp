#include"FrontInterface.hpp"
#include"Startup.hpp"
#include"Battle.hpp"
#include"SystemData.hpp"




namespace gmbb{


const Image&
update_screen() noexcept
{
  return screen::update(sys::root_task);
}


void
to_battle(int  retval) noexcept
{
  terminate_party_making();

  sav::fullrecover_all_heroes();

  start_battle(nullptr,ro::enemy_party_table[0]);
}


void
initialize() noexcept
{
#ifdef EMSCRIPTEN
        sys::glset.load_from_file("small_font.gz");
  sys::large_glset.load_from_file("large_font.gz");

#else
        sys::glset.load_from_file("/usr/local/share/gmbb/small_font.gz");
  sys::large_glset.load_from_file("/usr/local/share/gmbb/large_font.gz");
#endif


  ro::load();

  screen::enable_render();
  screen::set_fill_color(black);

  start_party_making(to_battle);
}


void
step(Controller const&  ctrl)
{
//  process_event();

  sys::root_task.update();

  call_routine(ctrl);
}


}




