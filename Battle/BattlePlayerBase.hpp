#ifndef BattlePlayerBase_HPP
#define BattlePlayerBase_HPP


#include<cstdint>
#include<string>
#include"libgbdn/gbdn.hpp"
#include"libgbstd/ro_ptr.hpp"
#include"libgbstd/rw_ptr.hpp"
#include"libgbstd/unicode.hpp"
#include"BattleCommand.hpp"


class
NameBuffer
{
  char16_t  m_data[8] = {0};

  uint16_t  m_length=0;

public:
  const char16_t*  get_data() const noexcept{return m_data;}

  uint16_t  get_length() const noexcept{return m_length;}

  void  clear() noexcept
  {
    m_data[0] = 0;

    m_length = 0;
  }

  void  push(char16_t  c) noexcept{m_data[  m_length++] = c;}
  void   pop(           ) noexcept{m_data[--m_length  ] = 0;}

  std::string  to_string() const noexcept
  {
    std::string  s;

    auto  src = get_data();

      while(*src)
      {
        auto  p = gbstd::utf8_encoder(*src++).codes;

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
  std::string  m_name;

  int  m_body_strength;
  int  m_mind_strength;
  int        m_agility;
  int        m_defense;
  int      m_intellect;

  int  m_hp=0;
  int  m_mp=0;

  CommandTable  m_command_table;

public:
  PlayerBase() noexcept{}
  PlayerBase(std::string_view  name, const gbdn::list&  ls){load(name,ls);}

  void  set_name(std::string_view  new_name) noexcept{m_name = new_name;}

  const std::string&  get_name() const noexcept{return m_name;}

  int  get_body_strength() const noexcept{return m_body_strength;}
  int  get_mind_strength() const noexcept{return m_mind_strength;}
  int        get_agility() const noexcept{return m_agility;}
  int        get_defense() const noexcept{return m_defense;}
  int      get_intellect() const noexcept{return m_intellect;}

  int  get_hp() const noexcept{return m_hp;}
  int  get_mp() const noexcept{return m_mp;}

  const CommandTable&  get_command_table() const noexcept{return m_command_table;}

  void  refresh_command_table();

  void  load(std::string_view  name, const gbdn::list&  ls);

  void  print() const noexcept;

};




#endif




