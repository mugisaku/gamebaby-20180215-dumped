#ifndef GMBB_IntervalTimer_HPP
#define GMBB_IntervalTimer_HPP


#include<cstdint>


namespace gmbb{


class
IntervalTimer
{
  uint32_t  last=0;

  bool  available=false;

public:
  IntervalTimer() noexcept{}

  void   enable() noexcept{available =  true;}
  void  disable() noexcept{available = false;}

  bool  check_step(uint32_t  interval, uint32_t  now) noexcept
  {
      if(!available || ((last+interval) < now))
      {
        last += interval;

        return true;
      }


    return false;
  }

  bool  check(uint32_t  interval, uint32_t  now) noexcept
  {
      if(!available || ((last+interval) < now))
      {
        last = now;

        return true;
      }


    return false;
  }

};


}




#endif




