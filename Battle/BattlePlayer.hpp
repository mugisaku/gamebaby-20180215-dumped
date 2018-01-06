#ifndef BattlePlayer_HPP
#define BattlePlayer_HPP


#include"BattleHero.hpp"
#include"BattleEnemy.hpp"




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
  PlayerKind  m_kind=PlayerKind::null;

  union Data{
    gbstd::rw_ptr<Hero>    hero;
    gbstd::ro_ptr<Enemy>  enemy;

     Data(){}
    ~Data(){}

  } m_data;


  gbstd::rw_ptr<BattleTeam>       m_own_team;
  gbstd::rw_ptr<BattleTeam>  m_opposite_team;

  uint32_t  m_state_flags=0;

  OperationStyle  m_operation_style=OperationStyle::manual;

  int  m_hp_max;
  int  m_mp_max;

  ExperienceSet  m_expset;

  int  m_attack_strength;
  int  m_guard_strength;
  int  m_magic_strength;
  int  m_number_of_attacks;
  int  m_number_of_guards;
  int  m_number_of_magics;

  int  m_current_command_index;

public:
  Player() noexcept{}

  operator bool() const noexcept{return m_kind != PlayerKind::null;}

  bool  is_enemy() const noexcept{return m_kind == PlayerKind::enemy;}
  bool  is_hero() const noexcept{return m_kind == PlayerKind::hero;}

  bool  is_actable() const noexcept{return m_hp;}
  bool  is_alive() const noexcept{return m_hp;}

  void  set_team(BattleTeam&  own_team_, BattleTeam&  opposite_team_) noexcept;

  void  set_data(const Enemy&  ene) noexcept;
  void  set_data(       Hero&  hro) noexcept;

  void  unset_data() noexcept;

  gbstd::rw_ptr<BattleTeam>  get_own_team()      const noexcept{return      m_own_team;}
  gbstd::rw_ptr<BattleTeam>  get_opposite_team() const noexcept{return m_opposite_team;}

  void                  set_current_command(int  i) noexcept{m_current_command_index = i;}
  const BattleCommand*  get_current_command() const noexcept{return m_command_table.commands[m_current_command_index];}

  void  set_operation_style(OperationStyle  op) noexcept{m_operation_style = op;}
  OperationStyle  get_operation_style() const noexcept{return m_operation_style;}

  bool  is_manual() const noexcept{return m_operation_style == OperationStyle::manual;}
  bool  is_automatic() const noexcept{return m_operation_style == OperationStyle::automatic;}

  int  get_hp_max() const noexcept{return m_hp_max;}
  int  get_hp() const noexcept{return m_hp;}
  int  get_mp_max() const noexcept{return m_mp_max;}
  int  get_mp() const noexcept{return m_mp;}

  const ExperienceSet&  get_experience_set() const noexcept{return m_expset;}

  int  get_attack_strength() const noexcept{return m_attack_strength;}
  int  get_guard_strength() const noexcept{return m_guard_strength;}
  int  get_magic_strength() const noexcept{return m_magic_strength;}
  int  get_number_of_attacks() const noexcept{return m_number_of_attacks;}
  int  get_number_of_guards() const noexcept{return m_number_of_guards;}
  int  get_number_of_magics() const noexcept{return m_number_of_magics;}

  int  calculate_attack_strength() const noexcept;
  int  calculate_guard_strength() const noexcept;
  int  calculate_magic_strength() const noexcept;
  int  calculate_number_of_attacks() const noexcept;
  int  calculate_number_of_guards() const noexcept;
  int  calculate_number_of_magics() const noexcept;
  void  update() noexcept;

  void  replenish_hp() noexcept{m_hp = m_hp_max;}
  void  replenish_mp() noexcept{m_mp = m_mp_max;}

  void  receive_hp_damage(int  v) noexcept;
  void  receive_hp_recover(int  v) noexcept;
  void  receive_mp_damage(int  v) noexcept;
  void  receive_mp_recover(int  v) noexcept;

  void  die() noexcept{m_hp = 0;}

};


class
PlayerReference
{
  static Player  default_entity;

  Player*  m_pointer;

public:
  PlayerReference(           ) noexcept: m_pointer(&default_entity){}
  PlayerReference(Player&  pl) noexcept: m_pointer(&pl){}

  PlayerReference&  operator=(Player&  pl) noexcept
  {
    m_pointer = &pl;

    return *this;
  }

  Player&  get() const noexcept{return *m_pointer;}

  operator Player&() const noexcept{return *m_pointer;}

};




#endif




