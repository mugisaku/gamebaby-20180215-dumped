#include"BattlePlayer.hpp"




Player
PlayerReference::
default_entity;




void
Player::
set_team(BattleTeam&  own_team_, BattleTeam&  opposite_team_) noexcept
{
  m_own_team      = &own_team_;
  m_opposite_team = &opposite_team_;
}


void
Player::
set_data(const Enemy&  ene) noexcept
{
  m_kind = PlayerKind::enemy;

  m_data.enemy = &ene;

  static_cast<PlayerBase&>(*this) = ene;

  m_hp_max = m_hp;
  m_mp_max = m_mp;

  update();
}


void
Player::
set_data(Hero&  hro) noexcept
{
  m_kind = PlayerKind::hero;

  m_data.hero = &hro;

  static_cast<PlayerBase&>(*this) = hro;

  m_hp_max = m_hp                 ;
             m_hp = hro.current_hp;

  m_mp_max = m_mp                 ;
             m_mp = hro.current_mp;

  update();
}


void
Player::
unset_data() noexcept
{
  m_kind = PlayerKind::null;
}




int
Player::
calculate_attack_strength() const noexcept
{
  return(m_body_strength*2)+(m_expset.attack/16);
}


int
Player::
calculate_guard_strength() const noexcept
{
  return m_defense+(m_body_strength/2)+(m_expset.guard/16);
}


int
Player::
calculate_magic_strength() const noexcept
{
  return(m_mind_strength*2)+(m_expset.magic/16);
}


int
Player::
calculate_number_of_attacks() const noexcept
{
  return 1+(m_agility/16)+(m_expset.attack/32);
}


int
Player::
calculate_number_of_guards() const noexcept
{
  return 1+(m_agility/24)+(m_expset.guard/16)+(m_expset.damage/16);
}


int
Player::
calculate_number_of_magics() const noexcept
{
  return 1+(m_agility/16)+(m_expset.magic/16);
}


void
Player::
update() noexcept
{
  m_attack_strength = calculate_attack_strength();
  m_guard_strength = calculate_guard_strength();
  m_magic_strength = calculate_magic_strength();

  m_number_of_attacks = calculate_number_of_attacks();
  m_number_of_guards = calculate_number_of_guards();
  m_number_of_magics = calculate_number_of_magics();
}


void
Player::
receive_hp_damage(int  v) noexcept
{
  m_hp -= v;

    if(m_hp <= 0)
    {
      die();
    }
}


void
Player::
receive_hp_recover(int  v) noexcept
{
  m_hp += v;

    if(m_hp >= m_hp_max)
    {
      m_hp = m_hp_max;
    }
}


void
Player::
receive_mp_damage(int  v) noexcept
{
  m_mp -= v;

    if(m_mp < 0)
    {
      m_mp = 0;
    }
}


void
Player::
receive_mp_recover(int  v) noexcept
{
  m_mp += v;

    if(m_mp > m_mp_max)
    {
      m_mp = m_mp_max;
    }
}




