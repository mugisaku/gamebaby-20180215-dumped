#include"gmbb_Window.hpp"
#include<cstdlib>




namespace gmbb{




void
Window::
resize(int  w, int  h) noexcept
{
  width_max  = w;
  height_max = h;

  set_state(WindowState::full_opened);
}


void
Window::
set_state(WindowState  st) noexcept
{
  state = st;

    switch(state)
    {
  case(WindowState::hidden):
      break;
  case(WindowState::open_to_down):
      width  = width_max;
      height =        16;
      break;
  case(WindowState::close_to_left):
  case(WindowState::close_to_up):
  case(WindowState::full_opened):
      width  = width_max;
      height = height_max;
      break;
  case(WindowState::open_to_right):
      width  =         16;
      height = height_max;
      break;
    }
}




void
Window::
change_border0_color(ColorIndex  ci) noexcept
{
  pixels[2] = ci;
}


void
Window::
change_border1_color(ColorIndex  ci) noexcept
{
  pixels[2] = ci;
}


void
Window::
change_surface_color(ColorIndex  ci) noexcept
{
  pixels[1] = ci;
}




void
Window::
animate() noexcept
{
  constexpr int  step = 8;

    switch(state)
    {
  case(WindowState::hidden):
  case(WindowState::full_opened):
      break;
  case(WindowState::open_to_right):
        if(width < width_max)
        {
          width += step;

            if(width >= width_max)
            {
              width = width_max;

              state = WindowState::full_opened;
            }
        }
      break;
  case(WindowState::close_to_left):
        if(width > 16)
        {
          width -= step;

            if(width <= 16)
            {
              width = 16;

              state = WindowState::hidden;
            }
        }
      break;
  case(WindowState::open_to_down):
        if(height < height_max)
        {
          height += step;

            if(height >= height_max)
            {
              height = height_max;

              state = WindowState::full_opened;
            }
        }
      break;
  case(WindowState::close_to_up):
        if(height > 16)
        {
          height -= step;

            if(height <= 16)
            {
              height = 16;

              state = WindowState::hidden;
            }
        }
      break;
    }
}


void
Window::
render(Image&  dst, Point  offset) const noexcept
{
    if(state != WindowState::hidden)
    {
      draw_frame(dst,offset);
    }
}




}




