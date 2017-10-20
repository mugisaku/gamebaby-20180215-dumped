#ifndef GMBB_RANDOM_NUMBER_HPP_INCLUDED
#define GMBB_RANDOM_NUMBER_HPP_INCLUDED


#include<cstdint>


namespace gmbb{


class
RandomNumber
{
  uint32_t  x;
  uint32_t  y;
  uint32_t  z;
  uint32_t  w;

public:
  RandomNumber(                                                      ) noexcept;
  RandomNumber(uint32_t  x_, uint32_t  y_, uint32_t  z_, uint32_t  w_) noexcept;

  void  reset(                                                      ) noexcept;
  void  reset(uint32_t  x_, uint32_t  y_, uint32_t  z_, uint32_t  w_) noexcept;

  uint32_t  generate(             ) noexcept;
  uint32_t  generate(uint32_t  max) noexcept;

};


}


#endif




