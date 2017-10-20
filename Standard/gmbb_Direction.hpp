#ifndef gmbb_Direction_HPP
#define gmbb_Direction_HPP


namespace gmbb{


enum class
Direction
{
        front,
   front_left,
         left,
    back_left,
         back,
   back_right,
        right,
  front_right,

  last = front_right,

  unknown,
  error,
};


constexpr Direction
get_opposite(Direction  d) noexcept
{
  return (d == Direction::front      )? Direction::back
        :(d == Direction::front_left )? Direction::back_right
        :(d == Direction::left       )? Direction::right
        :(d == Direction::back_left  )? Direction::front_right
        :(d == Direction::back       )? Direction::front
        :(d == Direction::back_right )? Direction::front_left
        :(d == Direction::right      )? Direction::left
        :(d == Direction::front_right)? Direction::back_left
        :Direction::unknown;
         
}


constexpr Direction
get_left(Direction  d) noexcept
{
  return (d == Direction::front      )? Direction::front_left
        :(d == Direction::front_left )? Direction::left
        :(d == Direction::left       )? Direction::back_left
        :(d == Direction::back_left  )? Direction::back
        :(d == Direction::back       )? Direction::back_right
        :(d == Direction::back_right )? Direction::right
        :(d == Direction::right      )? Direction::front_right
        :(d == Direction::front_right)? Direction::front
        :Direction::unknown;
         
}


constexpr Direction
get_right(Direction  d) noexcept
{
  return (d == Direction::front      )? Direction::front_right
        :(d == Direction::front_left )? Direction::front
        :(d == Direction::left       )? Direction::front_left
        :(d == Direction::back_left  )? Direction::left
        :(d == Direction::back       )? Direction::back_left
        :(d == Direction::back_right )? Direction::back
        :(d == Direction::right      )? Direction::back_right
        :(d == Direction::front_right)? Direction::right
        :Direction::unknown;
         
}


constexpr int
abs(int  n) noexcept
{
  return (n < 0)? -n:n;
}


constexpr int
get_distance(Direction  a, Direction  b) noexcept
{
  auto  diff = abs(static_cast<int>(a)-static_cast<int>(b));

  return (diff <= 4)? diff:8-diff;
}


constexpr Direction
get_farer(Direction  base, Direction  a, Direction  b) noexcept
{
  return get_distance(base,a) < get_distance(base,b)? b:a;
}


constexpr Direction
get_nearer(Direction  base, Direction  a, Direction  b) noexcept
{
  return get_distance(base,a) < get_distance(base,b)? a:b;
}


}




#endif




