#ifndef game_Character_HPP
#define game_Character_HPP


#include<cstdint>
#include<string>
#include"Pointer.hpp"


namespace gmbb{


enum class
ClassID
{
  null,
  warrior,
  hunter,
  thief,

};


struct
ClassData
{
  ClassID  id;

  const char*  name;

  int  strength_of_attack=0;
  int    number_of_attacks=0;

  int  strength_of_guard=0;
  int    number_of_guards=0;

};


constexpr int  hp_max = 9999;
constexpr int  mp_max =  999;


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

};


struct
CharacterData
{
  char  name[32] = {0};

  ClassData  class_data;

  int  hp=hp_max;
  int  mp=mp_max;

  void  set_name(const char*  new_name) noexcept;
  void  set_name(const NameBuffer&  nambuf) noexcept;

  

};


enum class
ActionKind
{
  null,
  attack,
  guard,

};


enum class
TargetKind
{
  null,
  one,
  all_of_heroes_side,
  all_of_enemies_side,

};


struct
Action
{
  ActionKind  kind;

  rw_ptr<CharacterData>   actor;
  rw_ptr<CharacterData>  target;

  TargetKind  target_kind;

};


}




#endif




