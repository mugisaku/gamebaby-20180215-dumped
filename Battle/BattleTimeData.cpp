#include"BattleTimeData.hpp"


namespace gmbb{


namespace{
constexpr int  number_of_heroes  = 4;
constexpr int  number_of_enemies = 6;

Player
players[number_of_heroes+number_of_enemies];
}


BattleTeam    hero_team(make_rw(players[               0]),number_of_heroes);
BattleTeam   enemy_team(make_rw(players[number_of_heroes]),number_of_enemies);


namespace tmp{
rw_ptr<Player>  player_pointer;
}


void
clear_player_all() noexcept
{
    for(auto&  p: hero_team)
    {
      p.unset_data();

      p.die();

      p.set_team(hero_team,enemy_team);
    }


    for(auto&  p: enemy_team)
    {
      p.unset_data();

      p.die();

      p.set_team(enemy_team,hero_team);
    }
}


}




