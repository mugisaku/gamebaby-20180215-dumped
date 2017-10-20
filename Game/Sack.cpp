#include"Sack.hpp"
#include"gmbb_Standard.hpp"




namespace gmbb{




Sack::
Sack() noexcept
{
    for(int  i = 0;  i < sack_capacity;  ++i)
    {
      pointer_table[i] = &value_table[i];
    }
}




namespace{
bool
compare(GameItem const*  a, GameItem const*  b)
{
  return *a < *b;
}
}


void
Sack::
sort() noexcept
{
  std::stable_sort(std::begin(pointer_table),std::end(pointer_table),compare);
}


void
Sack::
clear() noexcept
{
    for(auto&  i: value_table)
    {
      i = GameItem();
    }
}


covered_ptr<GameItem>
Sack::
find_empty() noexcept
{
    for(auto&  v: value_table)
    {
        if(!v)
        {
          return &v;
        }
    }


  return nullptr;
}


bool
Sack::
try_to_push_item(GameItem const&  item) noexcept
{
  auto  p = find_empty();

    if(p)
    {
      *p = item;

      return true;
    }


  return false;
}


void
Sack::
randomize() noexcept
{
  clear();


  gmbb::RandomNumber  r;

  auto  arr = GameItemSpecs::get();

    for(auto&  i: value_table)
    {
      i = GameItem(r.generate(8000)&1? &arr.first[r.generate(arr.second-1)]:nullptr);
    }


  sort();
}


}




