#include"gmbb_RandomNumber.hpp"
#include<random>




namespace gmbb{
namespace random_number{


namespace{


std::default_random_engine
engine;


}


void
initialize() noexcept
{
  engine = std::default_random_engine(std::random_device()());
}


double
UniformDistribution::
operator()(double  min, double  max) const noexcept
{
  std::uniform_real_distribution<>  dist(min,max);

  return dist(engine);
}


double
NormalDistribution::
operator()(double  mean, double  stddev) const noexcept
{
  std::normal_distribution<>  dist(mean,stddev);

  return dist(engine);
}




void
Seed::
reset() noexcept
{
  std::random_device  randev;

  x = randev();
  y = randev();
  z = randev();
  w = randev();
}


void
Seed::
reset(uint32_t  x_, uint32_t  y_, uint32_t  z_, uint32_t  w_) noexcept
{
  x = x_;
  y = y_;
  z = z_;
  w = w_;
}


}}




