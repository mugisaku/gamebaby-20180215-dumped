#ifndef GMBB_LineMaker_HPP_INCLUDED
#define GMBB_LineMaker_HPP_INCLUDED


#include"gmbb_Figures.hpp"




namespace gmbb{


class
LineMaker
{
  static constexpr int  shift_amount = 16;

  Point  point;

  int  distance;

  int  x_add_amount;
  int  y_add_amount;

public:
  LineMaker(Line  ln) noexcept;

  int  get_distance() const noexcept{return distance;}

  Point  get_point() const noexcept;

  void  step() noexcept;

};


}




#endif




