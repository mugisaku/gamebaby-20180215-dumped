#include"gmbb_RandomNumber.hpp"
#include<random>




namespace gmbb{
namespace random_number{


namespace{


std::default_random_engine
engine;


std::vector<std::uniform_real_distribution<>>
uniform_table;


std::vector<std::normal_distribution<>>
normal_table;


}


void
initialize() noexcept
{
  engine = std::default_random_engine(std::random_device()());
}


Descriptor
add_uniform(double  min, double  max) noexcept
{
  auto  i = uniform_table.size();

  uniform_table.emplace_back(min,max);

  return Descriptor((i<<16)|1);
}


Descriptor
add_normal(double  mean, double  stddev) noexcept
{
  auto  i = uniform_table.size();

  normal_table.emplace_back(mean,stddev);

  return Descriptor((i<<16)|2);
}


double
Descriptor::
operator()() const noexcept
{
  auto  i = value>>16;

    switch(value&3)
    {
  case(1): return uniform_table[i](engine);break;
  case(2): return  normal_table[i](engine);break;
    }


  return 0;
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




