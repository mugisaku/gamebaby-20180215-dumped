#ifndef GMBB_WINDOW_HPP
#define GMBB_WINDOW_HPP


#include"gmbb_Task.hpp"


namespace gmbb{


enum class
WindowState
{
  hidden,

  full_opened,

  open_to_down,
  open_to_right,
  close_to_up,
  close_to_left,

};


class
Window: public Task
{
protected:
  WindowState  state=WindowState::hidden;

  Pixel  pixels[4] = {Pixel(predefined_color_index::null),
                      Pixel(predefined_color_index::blue      ,30000),
                      Pixel(predefined_color_index::white     ,30000),
                      Pixel(predefined_color_index::light_gray,30000)};

  int   width    =0;
  int   width_max=0;
  int  height    =0;
  int  height_max=0;

  void  draw_frame(Image&  dst, Point  offset) const noexcept;

public:
  Window(              ) noexcept{}
  Window(int  w, int  h, Point  pt) noexcept: Task(pt){resize(w,h);}

  void  resize(int  w, int  h) noexcept;

  bool  operator==(WindowState  st) const noexcept{return state == st;}
  bool  operator!=(WindowState  st) const noexcept{return state != st;}

  WindowState  get_state() const noexcept{return state;}
  void  set_state(WindowState  st) noexcept;

  void  change_border0_color(ColorIndex  ci) noexcept;
  void  change_border1_color(ColorIndex  ci) noexcept;
  void  change_surface_color(ColorIndex  ci) noexcept;

  void  animate() noexcept;

  void  render(Image&  dst, Point  offset) const noexcept override;

};



}




#endif




