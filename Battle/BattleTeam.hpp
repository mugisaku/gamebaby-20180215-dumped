#ifndef BattleTeam_HPP
#define BattleTeam_HPP


#include"BattlePlayer.hpp"


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

  int  get_number_of_players() const noexcept{return number_of_players;}

  rw_ptr<Player>  get_alive_someone() noexcept;


  rw_ptr<Player>  begin() const noexcept{return (players                  );}
  rw_ptr<Player>    end() const noexcept{return (players+number_of_players);}

};


}




#endif




