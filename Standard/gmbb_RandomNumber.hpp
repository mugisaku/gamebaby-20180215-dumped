#ifndef GMBB_RANDOM_NUMBER_HPP_INCLUDED
#define GMBB_RANDOM_NUMBER_HPP_INCLUDED


#include<cstdint>


namespace gmbb{
namespace random_number{


class
Descriptor
{
  uint32_t  value;

public:
  Descriptor(uint32_t  v=0) noexcept: value(v){}

  operator bool() const noexcept{return value;}

  double  operator()() const noexcept;

};


void  initialize() noexcept;

Descriptor  add_normal(double  mean, double  stddev) noexcept;
Descriptor  add_uniform(double  min, double  max) noexcept;


struct
Seed
{
  uint32_t  x;
  uint32_t  y;
  uint32_t  z;
  uint32_t  w;

  Seed(                                                      ) noexcept{reset(           );}
  Seed(uint32_t  x_, uint32_t  y_, uint32_t  z_, uint32_t  w_) noexcept{reset(x_,y_,z_,w_);}

  void  reset(                                                      ) noexcept;
  void  reset(uint32_t  x_, uint32_t  y_, uint32_t  z_, uint32_t  w_) noexcept;

};


template<typename  T>
void
fill(T  begin, T  end, Seed  seed=Seed()) noexcept
{
    while(begin != end)
    {
      uint32_t  t = seed.x ^ (seed.x << 11);

      seed.x = seed.y;
      seed.y = seed.z;
      seed.z = seed.w;

                 seed.w = (seed.w ^ (seed.w >> 19)) ^ (t ^ (t >> 8)); 
      *begin++ = seed.w                                             ;
    }
}


}}


#endif




