#include"Game/Game.hpp"
#include<SDL.h>
#include<cstdlib>


#ifdef EMSCRIPTEN
#include<emscripten.h>
#endif



using namespace gmbb;


namespace{


SDL_Window*    window;
SDL_Surface*  surface;


Palette
palette;


Controller
ctrl;


template<typename  T>
void
write(uint8_t*&  ptr, int  pitch, uint32_t  v)
{
  auto  dst = reinterpret_cast<T*>(ptr);

  *dst++ = v;
  *dst   = v;


  dst = reinterpret_cast<T*>(ptr+pitch);

  *dst++ = v;
  *dst   = v;

  ptr += sizeof(T)*2;
}


void
transfer(const Image&  img)
{
  auto  base_ptr = static_cast<uint8_t*>(surface->pixels);

  const int  w     = img.get_width();
  const int  h     = img.get_height();
  const int  pitch = surface->pitch;
  const int  bps   = surface->format->BytesPerPixel;

  SDL_LockSurface(surface);

    for(int  y = 0;  y < h;  y += 1)
    {
      auto  ptr = base_ptr           ;
                  base_ptr += pitch*2;

        for(int  x = 0;  x < w;  x += 1)
        {
          auto  color = img.get_pixel_color(x,y,palette);

            switch(bps)
            {
          case(1):
              write<uint8_t>(ptr,pitch,color);
              break;
          case(2):
              write<uint16_t>(ptr,pitch,color);
              break;
          case(4):
              write<uint32_t>(ptr,pitch,color);
              break;
            }
        }
    }


  SDL_UnlockSurface(surface);

  SDL_UpdateWindowSurface(window);
}




void
quit()
{
  SDL_DestroyWindow(window);

  SDL_Quit();

  std::exit(0);
}


void
process_key_down(const SDL_KeyboardEvent&  evt)
{
  if(!evt.repeat)
  {
      switch(evt.keysym.sym)
      {
    case(SDLK_UP   ): ctrl.set(   Controller::up_button_flag);break;
    case(SDLK_LEFT ): ctrl.set( Controller::left_button_flag);break;
    case(SDLK_RIGHT): ctrl.set(Controller::right_button_flag);break;
    case(SDLK_DOWN ): ctrl.set( Controller::down_button_flag);break;

    case(SDLK_SPACE ): ctrl.set(Controller::start_button_flag);break;
    case(SDLK_LSHIFT):
    case(SDLK_RSHIFT): ctrl.set(Controller::shift_button_flag);break;

    case(SDLK_RETURN):
    case(SDLK_z):
        ctrl.set(Controller::p_button_flag);
        break;
    case(SDLK_RCTRL):
    case(SDLK_LCTRL):
    case(SDLK_x    ):
        ctrl.set(Controller::n_button_flag);
        break;
    case(SDLK_F1):
        SDL_SaveBMP(surface,"__SCREEN.bmp");
        break;
      }
  }
}


void
process_key_up(const SDL_KeyboardEvent&  evt)
{
    switch(evt.keysym.sym)
    {
  case(SDLK_UP   ): ctrl.unset(   Controller::up_button_flag);break;
  case(SDLK_LEFT ): ctrl.unset( Controller::left_button_flag);break;
  case(SDLK_RIGHT): ctrl.unset(Controller::right_button_flag);break;
  case(SDLK_DOWN ): ctrl.unset( Controller::down_button_flag);break;

  case(SDLK_SPACE ): ctrl.unset(Controller::start_button_flag);break;
  case(SDLK_LSHIFT):
  case(SDLK_RSHIFT): ctrl.unset(Controller::shift_button_flag);break;

  case(SDLK_RETURN):
  case(SDLK_z     ):
      ctrl.unset(Controller::p_button_flag);
      break;
  case(SDLK_RCTRL):
  case(SDLK_LCTRL):
  case(SDLK_x    ):
      ctrl.unset(Controller::n_button_flag);
      break;
    }
}


void
process_mouse_button(const SDL_MouseButtonEvent&  evt)
{
  ctrl.change_point(evt.x,evt.y);
}


void
process_mouse_motion(const SDL_MouseMotionEvent&  evt)
{
  ctrl.change_point(evt.x,evt.y);
}


void
main_loop()
{
  static SDL_Event  evt;

    while(SDL_PollEvent(&evt))
    {
        switch(evt.type)
        {
      case(SDL_KEYDOWN): process_key_down(evt.key);break;
      case(SDL_KEYUP  ): process_key_up(  evt.key);break;
      case(SDL_MOUSEBUTTONUP  ): process_mouse_button(evt.button);break;
      case(SDL_MOUSEBUTTONDOWN): process_mouse_button(evt.button);break;
      case(SDL_MOUSEMOTION): process_mouse_motion(evt.motion);break;
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


  static uint32_t  next;

  constexpr uint32_t  interval = 40;

  auto  now = SDL_GetTicks();

  ctrl.change_time(now);

    if(now >= next)
    {
      step(ctrl);

      next += interval;

        while(now >= next)
        {
          step(ctrl);

          next += interval;
        }


      transfer(update_screen());
    }
}


}


int
main(int  argc, char**  argv)
{
  initialize();


  SDL_Init(SDL_INIT_VIDEO);

  SDL_ShowCursor(SDL_DISABLE);

  auto&  img = update_screen();

  window = SDL_CreateWindow("GAME BABY - " __DATE__,SDL_WINDOWPOS_CENTERED,
                                                    SDL_WINDOWPOS_CENTERED,
                                                    img.get_width()*2,
                                                    img.get_height()*2,0);

  surface = SDL_GetWindowSurface(window);

    for(int  r = 0;  r < 8;  ++r){
    for(int  g = 0;  g < 8;  ++g){
    for(int  b = 0;  b < 8;  ++b){
      ColorIndex  i(r,g,b);

      auto  color = SDL_MapRGB(surface->format,i.r255(),i.g255(),i.b255());

      palette.set_color(i,color);
    }}}



#ifdef EMSCRIPTEN
  emscripten_set_main_loop(main_loop,0,true);
#else
    for(;;)
    {
      main_loop();

      SDL_Delay(20);
    }
#endif


  return 0;
}




