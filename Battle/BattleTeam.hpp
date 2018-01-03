#ifndef BattleTeam_HPP
#define BattleTeam_HPP


#include"BattlePlayer.hpp"
#include<vector>




class
BattleTeam
{
  gbstd::rw_ptr<Player>  m_players;

  int  m_number_of_players;

public:
  BattleTeam(gbstd::rw_ptr<Player>  begin, int  n) noexcept:
  m_players(begin),
  m_number_of_players(n){}

  Player&  operator[](int  i) const noexcept{return m_players[i];}

  using PlayerList = std::vector<PlayerReference>;

  bool  can_continue_to_battle() const noexcept;

  int  get_number_of_alive_players() const noexcept;

  int  collect_alive_players(PlayerList&  ls) const noexcept;

  gbstd::rw_ptr<Player>  pickup_target_player() const noexcept;


  gbstd::rw_ptr<Player>  begin() const noexcept{return (m_players                    );}
  gbstd::rw_ptr<Player>    end() const noexcept{return (m_players+m_number_of_players);}

};




#endif




