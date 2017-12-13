#include"BattleTimeData.hpp"


namespace gmbb{


namespace{
constexpr int  number_of_heroes  = 4;
constexpr int  number_of_enemies = 6;


Player
players[number_of_heroes+number_of_enemies];


rw_ptr<Player>
player_iterator = std::begin(players);


}


BattleTeam    hero_team(make_rw(players[               0]),number_of_heroes);
BattleTeam   enemy_team(make_rw(players[number_of_heroes]),number_of_enemies);


Player&
get_current_player() noexcept
{
  return *player_iterator;
}


void
rewind_player_iterator() noexcept
{
  player_iterator = std::begin(players);
}


bool
seek_previous_actable_player() noexcept
{
    while(player_iterator != std::begin(players))
    {
      --player_iterator;

        if(player_iterator->is_actable())
        {
          return true;
        }
    }


  return false;
}


bool
seek_next_actable_player() noexcept
{
    while(player_iterator != std::end(players))
    {
        if(player_iterator->is_actable())
        {
          return true;
        }


      ++player_iterator;
    }


  return false;
}


void
collect_actable_player(std::vector<reference_wrapper<Player>>&  buf) noexcept
{
    for(auto&  pl: players)
    {
        if(pl.is_actable())
        {
          buf.emplace_back(make_ref(pl));
        }
    }
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




