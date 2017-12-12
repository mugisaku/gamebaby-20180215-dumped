#include"BattleTeam.hpp"
#include<functional>


namespace gmbb{




bool
BattleTeam::
can_continue_to_battle() const noexcept
{
  return get_number_of_alive_players();
}


int
BattleTeam::
get_number_of_alive_players() const noexcept
{
  int  n = 0;

    for(auto&  pl: *this)
    {
        if(pl.is_alive())
        {
          ++n;
        }
    }


  return n;
}


int
BattleTeam::
collect_alive_players(PlayerList&  ls) const noexcept
{
  int  n = 0;

    for(auto&  pl: *this)
    {
        if(pl.is_alive())
        {
          ls.emplace_back(make_rw(pl));

          ++n;
        }
    }


  return n;
}


rw_ptr<Player>
BattleTeam::
pickup_target_player() const noexcept
{
    for(auto&  pl: *this)
    {
        if(pl.is_alive())
        {
          return make_rw(pl);
        }
    }


  return nullptr;
}


}




