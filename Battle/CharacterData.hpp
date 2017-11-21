#ifndef game_Character_HPP
#define game_Character_HPP


#include"Player.hpp"


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


struct
CharacterData
{
  char  name_buffer[32] = {0};

  ClassData  class_data;

};


}




#endif




