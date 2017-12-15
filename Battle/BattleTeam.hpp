#ifndef BattleTeam_HPP
#define BattleTeam_HPP


#include"BattlePlayer.hpp"
#include<vector>


namespace gmbb{


class
BattleTeam
{
  rw_ptr<Player>  players;

  int  number_of_players;

public:
  BattleTeam(rw_ptr<Player>  begin, int  n) noexcept:
  players(begin),
  number_of_players(n){}

  Player&  operator[](int  i) const noexcept{return players[i];}

  using PlayerList = std::vector<PlayerReference>;

  bool  can_continue_to_battle() const noexcept;

  int  get_number_of_alive_players() const noexcept;

  int  collect_alive_players(PlayerList&  ls) const noexcept;

  rw_ptr<Player>  pickup_target_player() const noexcept;


  rw_ptr<Player>  begin() const noexcept{return (players                  );}
  rw_ptr<Player>    end() const noexcept{return (players+number_of_players);}

};


}




#endif




