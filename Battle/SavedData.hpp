#ifndef game_SavedData_HPP
#define game_SavedData_HPP


#include"BattleHero.hpp"


namespace sav{


extern Hero  hero_table[4];


void  fullrecover_all_heroes() noexcept;


struct
Party
{
  static constexpr int  max_number_of_members = 4;

  gbstd::rw_ptr<Hero>  members[max_number_of_members] = {0};

  int  number_of_members = 0;


};


extern Party  party;


}




#endif




