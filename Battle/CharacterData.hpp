#ifndef game_Character_HPP
#define game_Character_HPP


#include<cstdint>
#include<string>


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

  int  strength_of_attack;
  int    number_of_attacks;

  int  strength_of_guard;
  int    number_of_guards;

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

  void  set_name(const NameBuffer&  nambuf) noexcept;

};


}




#endif




