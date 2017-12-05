#include"FrontInterface.hpp"
#include"Startup.hpp"
#include"Battle.hpp"
#include"SystemData.hpp"




namespace gmbb{


const Image&
update_screen() noexcept
{
  return screen::update(system_data::root_task);
}


void
to_battle(int  retval) noexcept
{
  terminate_party_making();

  start_battle(nullptr);
}


void
initialize() noexcept
{
#ifdef EMSCRIPTEN
        system_data::glset.load_from_file("small_font.gz");
  system_data::large_glset.load_from_file("large_font.gz");

#else
        system_data::glset.load_from_file("/usr/local/share/gmbb/small_font.gz");
  system_data::large_glset.load_from_file("/usr/local/share/gmbb/large_font.gz");
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

  system_data::root_task.update();

  call_routine(ctrl);
}


}




