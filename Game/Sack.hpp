#ifndef game_Sack_HPP
#define game_Sack_HPP


#include"GameItem.hpp"
#include"covered_ptr"
#include<algorithm>


namespace gmbb{


constexpr int  sack_capacity = 16;


class
Sack
{
  GameItem     value_table[sack_capacity];
  GameItem*  pointer_table[sack_capacity];

public:
  Sack() noexcept;

  GameItem&  get_item(int  i) noexcept{return *pointer_table[i];}

  void  clear() noexcept;

  covered_ptr<GameItem>  find_empty() noexcept;

  bool  try_to_push_item(GameItem const&  item) noexcept;

  void       sort() noexcept;
  void  randomize() noexcept;

};


}




#endif




