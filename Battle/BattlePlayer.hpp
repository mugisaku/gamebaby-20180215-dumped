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


class Side;
class Player;


struct
BattleAction
{
  ro_ptr<BattleCommand>  command;

  rw_ptr<Player>  target;

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


  rw_ptr<Side>       own_side;
  rw_ptr<Side>  opposite_side;

  int  hp_max;
  int  mp_max;

  ExperienceSet  expset;

  int  attack_strength;
  int  guard_strength;
  int  magic_strength;
  int  number_of_attacks;
  int  number_of_guards;
  int  number_of_magics;

  BattleAction  action;

public:
  Player() noexcept{}

  operator bool() const noexcept{return kind != PlayerKind::null;}

  bool  is_enemy() const noexcept{return kind == PlayerKind::enemy;}
  bool  is_hero() const noexcept{return kind == PlayerKind::hero;}

  bool  is_actable() const noexcept{return hp;}

  void  set_side(Side&  own_side_, Side&  opposite_side_) noexcept;

  void  set_data(const Enemy&  ene) noexcept;
  void  set_data(       Hero&  hro) noexcept;

  void  unset_data() noexcept;

  rw_ptr<Side>  get_own_side()      const noexcept{return      own_side;}
  rw_ptr<Side>  get_opposite_side() const noexcept{return opposite_side;}

  void  set_action(const BattleAction&  act) noexcept{action =act;}
  const BattleAction&  get_action() const noexcept{return action;}

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

  int  calculate_hp_max() const noexcept;
  int  calculate_mp_max() const noexcept;
  int  calculate_attack_strength() const noexcept;
  int  calculate_guard_strength() const noexcept;
  int  calculate_magic_strength() const noexcept;
  int  calculate_number_of_attacks() const noexcept;
  int  calculate_number_of_guards() const noexcept;
  int  calculate_number_of_magics() const noexcept;
  void  update() noexcept;

  void  replenish_hp() noexcept{hp = hp_max;}
  void  replenish_mp() noexcept{mp = mp_max;}

};


struct
Side
{
  static constexpr int  number_of_players = 4;

  Player  players[number_of_players];

};


}




#endif




