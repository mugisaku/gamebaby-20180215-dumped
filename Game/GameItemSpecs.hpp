#ifndef game_GameItemSpecs_HPP
#define game_GameItemSpecs_HPP


#include<cstdint>
#include<cstddef>
#include<string>


namespace gmbb{


enum class
Condition
{
  null,
  sleep,
  poison,
  confuse,
  blind,
  illusion,
  seal,

};


enum class
GameItemKind
{
  null,

  sword,
  shield,
  belt,
  wand,
  card,
  water,

};


struct
SwordSpecs
{
  uint8_t  strength;

  constexpr SwordSpecs(int  str): strength(str){}

};


struct
ShieldSpecs
{
  uint8_t  strength;

  constexpr ShieldSpecs(int  str): strength(str){}

};


struct
BeltSpecs
{
  uint8_t  effect=0;

  constexpr BeltSpecs(){}

};


struct
WandSpecs
{
  uint8_t  effect=0;

  constexpr WandSpecs(){}

};


struct
CardSpecs
{
  uint8_t  effect=0;

  constexpr CardSpecs(){}

};


struct
WaterSpecs
{
  uint8_t  effect=0;

  constexpr WaterSpecs(){}

};


union
GameItemSpecsData
{
  SwordSpecs        sword;
  ShieldSpecs      shield;
  BeltSpecs          belt;
  WandSpecs          wand;
  CardSpecs          card;
  WaterSpecs        water;

   GameItemSpecsData() noexcept{}
  ~GameItemSpecsData()         {}

};


struct
Price
{
  int  value;

  constexpr Price(int  v=0) noexcept: value(v){}

};


class
GameItemSpecs
{
  char const*  name="";

  Price  price;

  char const*  description="";

  GameItemKind       kind=GameItemKind::null;
  GameItemSpecsData  data;

  GameItemSpecs() noexcept{}
  GameItemSpecs(char const*  name_, Price  pri, char const*  desc, SwordSpecs const&     swd) noexcept;
  GameItemSpecs(char const*  name_, Price  pri, char const*  desc, ShieldSpecs const&    shl) noexcept;
  GameItemSpecs(char const*  name_, Price  pri, char const*  desc, BeltSpecs const&  blt) noexcept;
  GameItemSpecs(char const*  name_, Price  pri, char const*  desc, WandSpecs const&  wnd) noexcept;
  GameItemSpecs(char const*  name_, Price  pri, char const*  desc, CardSpecs const&  crd) noexcept;
  GameItemSpecs(char const*  name_, Price  pri, char const*  desc, WaterSpecs const&  wat) noexcept;

public:
  static std::pair<GameItemSpecs const*,size_t>  get() noexcept;

  static GameItemSpecs const*  find_by_name(std::string const&  name) noexcept;

  GameItemSpecsData const*  operator->() const noexcept{return &data;}

  char const*  get_name() const noexcept{return name;}
  char const*  get_description() const noexcept{return description;}

  char const*  get_first_operation_name() const noexcept;

  GameItemKind  get_kind() const noexcept{return kind;}

  Price  get_price() const noexcept{return price;}

};


}




#endif




