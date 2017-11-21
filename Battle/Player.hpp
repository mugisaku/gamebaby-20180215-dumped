#ifndef game_player_HPP
#define game_player_HPP


#include<cstddef>


namespace gmbb{


struct
Player
{
  const char*        name;
  const char*  class_name;

  int  hp    ;
  int  hp_max;

  int  mp    ;
  int  mp_max;

  int        offense;
  int        defense;
  int  magic_offense;
  int  magic_defense;

  int  agility;

};


}




#endif




