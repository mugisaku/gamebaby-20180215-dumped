#include"gmbb_RandomNumber.hpp"
#include<random>




namespace gmbb{


namespace{
std::random_device
randev;
}


RandomNumber::
RandomNumber() noexcept
{
  reset();
}


RandomNumber::
RandomNumber(uint32_t  x_, uint32_t  y_, uint32_t  z_, uint32_t  w_) noexcept
{
  reset(x_,y_,z_,w_);
}




void
RandomNumber::
reset() noexcept
{
  x = randev();
  y = randev();
  z = randev();
  w = randev();
}


void
RandomNumber::
reset(uint32_t  x_, uint32_t  y_, uint32_t  z_, uint32_t  w_) noexcept
{
  x = x_;
  y = y_;
  z = z_;
  w = w_;
}


uint32_t
RandomNumber::
generate() noexcept
{
  uint32_t  t = x ^ (x << 11);

  x = y;
  y = z;
  z = w;

  w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)); 

  return w;
}


uint32_t
RandomNumber::
generate(uint32_t  max) noexcept
{
  auto  n = generate();

    if(!max)
    {
      return 0;
    }


  return n%max;
}


}




