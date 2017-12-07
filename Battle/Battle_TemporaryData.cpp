#include"Battle_TemporaryData.hpp"


namespace gmbb{


Side    hero_side;
Side   enemy_side;

rw_ptr<Player>  current_player;

Action  action;


void
clear_player_all() noexcept
{
    for(auto&  pl: hero_side.players)
    {
      pl.unset_data();

      pl.set_side(hero_side,enemy_side);
    }


    for(auto&  pl: enemy_side.players)
    {
      pl.unset_data();

      pl.set_side(enemy_side,hero_side);
    }
}


}




