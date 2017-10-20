#ifndef game_GameItem_HPP
#define game_GameItem_HPP


#include"GameItemSpecs.hpp"


namespace gmbb{


enum class
GameItemFlag
{
  equipped = 0x1,
  cursed   = 0x2,

};


class
GameItem
{
  GameItemSpecs const*  specs=nullptr;

  int  number=0;

  uint32_t  flags=0;

public:
  GameItem() noexcept{}
  GameItem(GameItemSpecs const*  specs_) noexcept: specs(specs_){}

  bool  operator<(GameItem const&  rhs) const noexcept;

  operator bool() const noexcept{return specs;}

  GameItemSpecs const*  operator->() const noexcept{return specs;}


  GameItemSpecs const&  get_specs() const noexcept{return *specs;}

  int  get_number() const noexcept{return number;}

  void    set_flag(GameItemFlag  flag)       noexcept{       flags |=  static_cast<int>(flag);}
  void  unset_flag(GameItemFlag  flag)       noexcept{       flags &= ~static_cast<int>(flag);}
  bool   test_flag(GameItemFlag  flag) const noexcept{return flags&static_cast<int>(flag);}

  bool  is_equipped() const noexcept{return test_flag(GameItemFlag::equipped);}
  bool    is_cursed() const noexcept{return test_flag(GameItemFlag::cursed);}

};


}




#endif




