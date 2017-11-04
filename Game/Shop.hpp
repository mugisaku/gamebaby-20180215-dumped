#ifndef game_Shop_HPP
#define game_Shop_HPP


#include"GameItemSpecs.hpp"
#include"gamn.hpp"


namespace gmbb{


struct
Commodity
{
  std::string  name;

  Price  price;

  int  number;

};


struct
ShopMessageSet
{
  gamn::ListNode const*  on_enter=nullptr;
  gamn::ListNode const*  on_exit =nullptr;

  gamn::ListNode const*  when_money_is_enough=nullptr;
  gamn::ListNode const*  when_money_is_not_enough=nullptr;
  gamn::ListNode const*  you_want_for_this=nullptr;

};


class
Shop
{
public:
  static constexpr int  table_size = 8;

private:
  std::string  name;

  Commodity  table[table_size];

  int  number=0;

  ShopMessageSet  message_set;

  void  read_commodity(gamn::ListNode const*  cur) noexcept;

public:
  Shop(std::string const&  name_, gamn::List const&  ls) noexcept;

  void  push(Commodity const&  comm) noexcept{table[number++] = comm;}

  ShopMessageSet const&  get_message_set() const noexcept{return message_set;}

  std::string const&  get_name() const noexcept{return name;}

  Commodity const&  get_commodity(int  i) noexcept{return table[i];}

  int  get_number_of_commodities() const noexcept{return number;}


};


}




#endif




