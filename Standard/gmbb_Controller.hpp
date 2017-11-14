#ifndef GMBB_CONTROLLER_HPP
#define GMBB_CONTROLLER_HPP


#include"gmbb_Figures.hpp"
#include<cstdint>
#include<cstdio>
#include<string>


namespace gmbb{


class
ButtonState
{
protected:
  uint32_t  flags=0;

public:
  void    set(uint32_t  flag)       noexcept{flags |=  flag;}
  void  unset(uint32_t  flag)       noexcept{flags &= ~flag;}
  bool   test(uint32_t  flag) const noexcept{return(flags&flag);}

  uint32_t  get() const noexcept{return flags;}

};


class
Controller: public ButtonState
{
  uint32_t  time=0;

  Point  point;

public:
  void  change_point(int  x, int  y){point = Point(x,y);}

  Point  get_point() const noexcept{return point;}

  void  change_time(uint32_t  v) noexcept{time = v;}

  uint32_t  get_time() const noexcept{return time;}


  static constexpr uint32_t       up_button_flag = 0x001;
  static constexpr uint32_t     left_button_flag = 0x002;
  static constexpr uint32_t    right_button_flag = 0x004;
  static constexpr uint32_t     down_button_flag = 0x008;
  static constexpr uint32_t        p_button_flag = 0x010;
  static constexpr uint32_t        n_button_flag = 0x020;
  static constexpr uint32_t    start_button_flag = 0x040;
  static constexpr uint32_t    shift_button_flag = 0x080;
  static constexpr uint32_t   mouse_lbutton_flag = 0x100;
  static constexpr uint32_t   mouse_rbutton_flag = 0x200;

  bool       is_up_button_pressing() const noexcept{return test(    up_button_flag);}
  bool     is_left_button_pressing() const noexcept{return test(  left_button_flag);}
  bool    is_right_button_pressing() const noexcept{return test( right_button_flag);}
  bool     is_down_button_pressing() const noexcept{return test(  down_button_flag);}
  bool        is_p_button_pressing() const noexcept{return test(     p_button_flag);}
  bool        is_n_button_pressing() const noexcept{return test(     n_button_flag);}
  bool    is_start_button_pressing() const noexcept{return test( start_button_flag);}
  bool    is_shift_button_pressing() const noexcept{return test( shift_button_flag);}
  bool   is_mouse_lbutton_pressing() const noexcept{return test(mouse_lbutton_flag);}
  bool   is_mouse_rbutton_pressing() const noexcept{return test(mouse_rbutton_flag);}


};


}


#endif




