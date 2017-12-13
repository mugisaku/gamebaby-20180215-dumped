#ifndef BattlePlayer_HPP
#define BattlePlayer_HPP


#include"BattleHero.hpp"
#include"BattleEnemy.hpp"


namespace gmbb{


enum class
PlayerKind
{
  null,
  hero,
  enemy,

};


class BattleTeam;
class Player;


constexpr uint32_t  alive_flag = 0x00001;


enum class
OperationStyle
{
  manual,
  automatic,
//  semi_automatic,
  
};


class
Player: public PlayerBase
{
  PlayerKind  kind=PlayerKind::null;

  union Data{
    rw_ptr<Hero>    hero;
    ro_ptr<Enemy>  enemy;

     Data(){}
    ~Data(){}

  } data;


  rw_ptr<BattleTeam>       own_team;
  rw_ptr<BattleTeam>  opposite_team;

  uint32_t  state_flags=0;

  OperationStyle  operation_style=OperationStyle::manual;

  int  hp_max;
  int  mp_max;

  ExperienceSet  expset;

  int  attack_strength;
  int  guard_strength;
  int  magic_strength;
  int  number_of_attacks;
  int  number_of_guards;
  int  number_of_magics;

  int  current_command_index;

public:
  static Player&  get_default();

  Player() noexcept{}

  operator bool() const noexcept{return kind != PlayerKind::null;}

  bool  is_enemy() const noexcept{return kind == PlayerKind::enemy;}
  bool  is_hero() const noexcept{return kind == PlayerKind::hero;}

  bool  is_actable() const noexcept{return hp;}
  bool  is_alive() const noexcept{return hp;}

  void  set_team(BattleTeam&  own_team_, BattleTeam&  opposite_team_) noexcept;

  void  set_data(const Enemy&  ene) noexcept;
  void  set_data(       Hero&  hro) noexcept;

  void  unset_data() noexcept;

  rw_ptr<BattleTeam>  get_own_team()      const noexcept{return      own_team;}
  rw_ptr<BattleTeam>  get_opposite_team() const noexcept{return opposite_team;}

  void  set_current_command(int  i) noexcept{current_command_index = i;}
  const BattleCommand&  get_current_command() const noexcept{return command_table.commands[current_command_index];}

  void  set_operation_style(OperationStyle  op) noexcept{operation_style = op;}
  OperationStyle  get_operation_style() const noexcept{return operation_style;}

  int  get_hp_max() const noexcept{return hp_max;}
  int  get_hp() const noexcept{return hp;}
  int  get_mp_max() const noexcept{return mp_max;}
  int  get_mp() const noexcept{return mp;}

  const ExperienceSet&  get_experience_set() const noexcept{return expset;}

  int  get_attack_strength() const noexcept{return attack_strength;}
  int  get_guard_strength() const noexcept{return guard_strength;}
  int  get_magic_strength() const noexcept{return magic_strength;}
  int  get_number_of_attacks() const noexcept{return number_of_attacks;}
  int  get_number_of_guards() const noexcept{return number_of_guards;}
  int  get_number_of_magics() const noexcept{return number_of_magics;}

  int  calculate_attack_strength() const noexcept;
  int  calculate_guard_strength() const noexcept;
  int  calculate_magic_strength() const noexcept;
  int  calculate_number_of_attacks() const noexcept;
  int  calculate_number_of_guards() const noexcept;
  int  calculate_number_of_magics() const noexcept;
  void  update() noexcept;

  void  replenish_hp() noexcept{hp = hp_max;}
  void  replenish_mp() noexcept{mp = mp_max;}

  void  receive_hp_damage(int  v) noexcept;
  void  receive_hp_recover(int  v) noexcept;
  void  receive_mp_damage(int  v) noexcept;
  void  receive_mp_recover(int  v) noexcept;

  void  die() noexcept{hp = 0;}

};


struct
Side
{
  static constexpr int  number_of_players = 4;

  Player  players[number_of_players];

  rw_ptr<Player>  get_alive_someone() noexcept;

};


}




#endif




