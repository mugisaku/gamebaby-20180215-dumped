#ifndef BattlePlayerBase_HPP
#define BattlePlayerBase_HPP


#include<cstdint>
#include<string>
#include"Pointer.hpp"
#include"gmbb_unicode.hpp"
#include"gbdn.hpp"
#include"BattleCommand.hpp"


namespace gmbb{


class
NameBuffer
{
  char16_t  data[8] = {0};

  uint16_t  length=0;

public:
  const char16_t*  get_data() const noexcept{return data;}

  uint16_t  get_length() const noexcept{return length;}

  void  clear() noexcept
  {
    data[0] = 0;

    length = 0;
  }

  void  push(char16_t  c) noexcept{data[  length++] = c;}
  void   pop(           ) noexcept{data[--length  ] = 0;}

  std::string  to_string() const noexcept
  {
    std::string  s;

    auto  src = get_data();

      while(*src)
      {
        auto  p = UTF8Chunk(*src++).codes;

          while(*p)
          {
            s += *p++;
          }
      }


    return std::move(s);
  }

};


constexpr int    human_flag = 0x0001;
constexpr int   female_flag = 0x0002;
constexpr int     male_flag = 0x0004;
constexpr int    plant_flag = 0x0008;
constexpr int    beast_flag = 0x0010;
constexpr int     fish_flag = 0x0020;
constexpr int   insect_flag = 0x0040;
constexpr int  machine_flag = 0x0080;
constexpr int    demon_flag = 0x0100;
constexpr int    giant_flag = 0x0200;
constexpr int   dragon_flag = 0x0400;
constexpr int  phantom_flag = 0x0800;
constexpr int   sacred_flag = 0x1000;
constexpr int    flyer_flag = 0x2000;
constexpr int   zombie_flag = 0x4000;


class
PlayerBase
{
protected:
  std::string  name;

  int  body_strength;
  int  mind_strength;
  int        agility;
  int        defense;
  int      intellect;

  int  hp=0;
  int  mp=0;

  BattleCommand  command_table[4];

//  Accessory  accessory_table[4];

//  Ability  ability_table[8];
public:
  PlayerBase() noexcept{}
  PlayerBase(const char*  name_, const gbdn::list&  ls) noexcept{load(name_,ls);}

  void  set_name(std::string&&  new_name) noexcept{name = new_name;}

  const std::string&  get_name() const noexcept{return name;}

  int  get_body_strength() const noexcept{return body_strength;}
  int  get_mind_strength() const noexcept{return mind_strength;}
  int        get_agility() const noexcept{return agility;}
  int        get_defense() const noexcept{return defense;}
  int      get_intellect() const noexcept{return intellect;}

  int  get_hp() const noexcept{return hp;}
  int  get_mp() const noexcept{return mp;}

  void  load(const char*  name_, const gbdn::list&  ls) noexcept;

};


}




#endif




