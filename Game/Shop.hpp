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


class
Shop
{
public:
  static constexpr int  table_size = 8;

private:
  std::string  name;

  Commodity  table[table_size];

  int  number=0;

  void  read_commodity(gamn::ListNode const*  cur) noexcept;

public:
  Shop(std::string const&  name_, gamn::List const&  ls) noexcept;

  void  push(Commodity const&  comm) noexcept{table[number++] = comm;}

  std::string const&  get_name() const noexcept{return name;}

  Commodity const&  get_commodity(int  i) noexcept{return table[i];}

  int  get_number_of_commodities() const noexcept{return number;}


};


}




#endif




