#include"libgbsnd/device.hpp"
#include"libgbsnd/script.hpp"
#include"libgbsnd/expr.hpp"
#include"libgbsnd/execution.hpp"


#include<SDL.h>
#include<cstdlib>



namespace{


SDL_Window*
window;


SDL_AudioSpec
spec;


SDL_AudioDeviceID
id;


gbsnd::script
script;


gbsnd::execution_context
ctx;


constexpr int  number_of_samples = 1024;

uint32_t
buffer[number_of_samples];


void
callback(void*  userdata, uint8_t*  buf, int  len)
{
  memset(buffer,0,sizeof(uint32_t)*len);

    for(auto&  sq: script.get_square_wave_list())
    {
      sq->output(buffer,&buffer[len]);
    }


    for(auto&  no: script.get_noise_list())
    {
      no->output(buffer,&buffer[len]);
    }


  auto  buf_end = buf+len;

  const uint32_t*  src = buffer;

    while(buf < buf_end)
    {
      auto  v = (*src++)>>16;

      *buf++ = (v > 0xFF)? 0xFF:v;
    }
}


void
initialize()
{
  spec.freq     = gbsnd::number_of_samples_per_seconds;
  spec.format   = AUDIO_S8;
  spec.samples  = number_of_samples;
  spec.channels = 1;
  spec.callback = callback;

	 id = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0,0),0,&spec,nullptr,0);

  SDL_PauseAudioDevice(id,0);
}


void
quit()
{
  SDL_CloseAudioDevice(id);

  SDL_DestroyWindow(window);

  SDL_Quit();

  fflush(stdout);

  std::_Exit(0);
}


void
main_loop()
{
  static SDL_Event  evt;

    while(SDL_PollEvent(&evt))
    {
        switch(evt.type)
        {
      case(SDL_WINDOWEVENT):
             switch(evt.window.event)
             {
           case(SDL_WINDOWEVENT_EXPOSED):
               break;
             }
           break;
      case(SDL_QUIT):
           quit();
           break;
        }
    }


  static uint32_t  last;

  auto  now = SDL_GetTicks();

  ctx.run(gbsnd::millisecond{now});

    if(now >= last+1000)
    {
      last = now;

      SDL_FillRect(SDL_GetWindowSurface(window),nullptr,0);

      SDL_UpdateWindowSurface(window);
    }
}


}


int
main(int  argc, char**  argv)
{
  script = gbsnd::script::build_from_file("../gb.snd.txt");


  constexpr int  w = 240;
  constexpr int  h = 240;

  SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);

  initialize();



  SDL_ShowCursor(SDL_DISABLE);

  window = SDL_CreateWindow("GAME BABY - " __DATE__,
0,0,
//                            SDL_WINDOWPOS_CENTERED,
//                            SDL_WINDOWPOS_CENTERED,
                            w,
                            h,0);


  ctx.reset(script);

  ctx.call("main",{});

    for(;;)
    {
      main_loop();

      SDL_Delay(20);
    }


  quit();

  return 0;
}




