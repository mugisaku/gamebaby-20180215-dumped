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

};


namespace flags_of_input{
constexpr uint32_t            none(0);
constexpr uint32_t       up_button( 0x001);
constexpr uint32_t     left_button( 0x002);
constexpr uint32_t    right_button( 0x004);
constexpr uint32_t     down_button( 0x008);
constexpr uint32_t        p_button( 0x010);
constexpr uint32_t        n_button( 0x020);
constexpr uint32_t    start_button( 0x040);
constexpr uint32_t    shift_button( 0x080);
constexpr uint32_t   mouse_lbutton( 0x100);
constexpr uint32_t   mouse_rbutton( 0x200);
}

}


#endif




