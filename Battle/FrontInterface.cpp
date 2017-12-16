#include"FrontInterface.hpp"
#include"Startup.hpp"
#include"Battle.hpp"
#include"SystemData.hpp"




namespace gmbb{


namespace{


const coprocess
main_coproc("main",[](uint32_t&  pc)
{
    switch(pc)
    {
  case(0):
      coprocesses::push(nullptr,coprocess_of_party_making);
      ++pc;
      break;
  case(1):
      terminate_party_making();

      sav::fullrecover_all_heroes();


      set_parties_of_battle(ro::enemy_party_table[0]);

      coprocesses::push(nullptr,coprocess_of_battle);
      ++pc;
      break;
  case(2):
      break;
  default:;
    }
});


}


const Image&
update_screen() noexcept
{
  return screen::update(sys::root_task);
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

  coprocesses::push(nullptr,main_coproc);
}


void
step()
{
//  process_event();

  sys::root_task.update();

  coprocesses::call();
}


}




