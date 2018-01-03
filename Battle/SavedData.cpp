#include"SavedData.hpp"


namespace sav{


Hero  hero_table[4];


Party  party;


void
fullrecover_all_heroes() noexcept
{
    for(auto&  hero: hero_table)
    {
      hero.current_hp = hero.get_hp();
      hero.current_mp = hero.get_mp();
    }
}


}




