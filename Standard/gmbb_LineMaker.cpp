#include"gmbb_LineMaker.hpp"
#include<algorithm>



namespace gmbb{


LineMaker::
LineMaker(Line  ln) noexcept
{
  constexpr int  base = (1<<shift_amount)/2;

  auto  const x_min = std::min(ln.a.x,ln.b.x);
  auto  const x_max = std::max(ln.a.x,ln.b.x);
  auto  const y_min = std::min(ln.a.y,ln.b.y);
  auto  const y_max = std::max(ln.a.y,ln.b.y);

  int  x_distance = x_max-x_min;
  int  y_distance = y_max-y_min;

  point.x = base+(ln.a.x<<shift_amount);
  point.y = base+(ln.a.y<<shift_amount);

    if(!x_distance)
    {
      x_add_amount = (0              );
      y_add_amount = (1<<shift_amount);

      distance = y_distance;
    }

  else
    if(!y_distance)
    {
      x_add_amount = (1<<shift_amount);
      y_add_amount = (0              );

      distance = x_distance;
    }

  else
    if(x_distance < y_distance)
    {
      x_add_amount = (x_distance<<shift_amount)/y_distance;
      y_add_amount = (         1<<shift_amount);

      distance = y_distance;
    }

  else
    if(x_distance > y_distance)
    {
      x_add_amount = (         1<<shift_amount);
      y_add_amount = (y_distance<<shift_amount)/x_distance;

      distance = x_distance;
    }

  else
    {
      x_add_amount = (1<<shift_amount);
      y_add_amount = (1<<shift_amount);

      distance = x_distance;
    }


    if(ln.a.x > ln.b.x){x_add_amount *= -1;}
    if(ln.a.y > ln.b.y){y_add_amount *= -1;}
}




Point
LineMaker::
get_point() const noexcept
{
  return Point(point.x>>shift_amount,
               point.y>>shift_amount);
}


void
LineMaker::
step() noexcept
{
  point.x += x_add_amount;
  point.y += y_add_amount;

  --distance;
}


}





