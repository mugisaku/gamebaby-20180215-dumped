#ifndef GMBB_IntervalTimer_HPP
#define GMBB_IntervalTimer_HPP


#include<cstdint>


namespace gmbb{


class
IntervalTimer
{
  uint32_t  last=0;

public:
  IntervalTimer() noexcept{}

  bool  check_step(uint32_t  interval, uint32_t  now) noexcept
  {
      if((last+interval) < now)
      {
        last += interval;

        return true;
      }


    return false;
  }

  bool  check(uint32_t  interval, uint32_t  now) noexcept
  {
      if((last+interval) < now)
      {
        last = now;

        return true;
      }


    return false;
  }

};


}




#endif




