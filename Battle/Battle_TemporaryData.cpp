#include"Battle_TemporaryData.hpp"


namespace gmbb{


Side    hero_side;
Side   enemy_side;

Action  action;


void
clear_player_all() noexcept
{
    for(auto&  pl: hero_side.players)
    {
      pl.unset_data();
    }


    for(auto&  pl: enemy_side.players)
    {
      pl.unset_data();
    }
}


}




