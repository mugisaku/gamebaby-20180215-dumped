#ifndef GMBB_RANDOM_NUMBER_HPP_INCLUDED
#define GMBB_RANDOM_NUMBER_HPP_INCLUDED


#include<cstdint>


namespace gmbb{
namespace random_number{


void  initialize() noexcept;


struct
NormalDistribution
{
  double  operator()(double  mean, double  stddev) const noexcept;

};


struct
UniformDistribution
{
  double  operator()(double  min, double  max) const noexcept;

};


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




