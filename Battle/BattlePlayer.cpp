#include"BattlePlayer.hpp"
#include"gmbb_unicode.hpp"


namespace gmbb{




Player&
Player::
get_default()
{
  static Player  dummy;

  return dummy;
}




void
Player::
set_team(BattleTeam&  own_team_, BattleTeam&  opposite_team_) noexcept
{
  own_team      = &own_team_;
  opposite_team = &opposite_team_;
}


void
Player::
set_data(const Enemy&  ene) noexcept
{
  kind = PlayerKind::enemy;

  data.enemy = &ene;

  static_cast<PlayerBase&>(*this) = ene;

  hp_max = hp;
  mp_max = mp;

  update();
}


void
Player::
set_data(Hero&  hro) noexcept
{
  kind = PlayerKind::hero;

  data.hero = &hro;

  static_cast<PlayerBase&>(*this) = hro;

  hp_max = hp                 ;
           hp = hro.current_hp;

  mp_max = mp                 ;
           mp = hro.current_mp;

  update();
}


void
Player::
unset_data() noexcept
{
  kind = PlayerKind::null;
}




int
Player::
calculate_attack_strength() const noexcept
{
  return(body_strength*2)+(expset.attack/16);
}


int
Player::
calculate_guard_strength() const noexcept
{
  return defense+(body_strength/2)+(expset.guard/16);
}


int
Player::
calculate_magic_strength() const noexcept
{
  return(mind_strength*2)+(expset.magic/16);
}


int
Player::
calculate_number_of_attacks() const noexcept
{
  return 1+(agility/16)+(expset.attack/32);
}


int
Player::
calculate_number_of_guards() const noexcept
{
  return 1+(agility/24)+(expset.guard/16)+(expset.damage/16);
}


int
Player::
calculate_number_of_magics() const noexcept
{
  return 1+(agility/16)+(expset.magic/16);
}


void
Player::
update() noexcept
{
  attack_strength = calculate_attack_strength();
  guard_strength = calculate_guard_strength();
  magic_strength = calculate_magic_strength();

  number_of_attacks = calculate_number_of_attacks();
  number_of_guards = calculate_number_of_guards();
  number_of_magics = calculate_number_of_magics();
}


void
Player::
receive_hp_damage(int  v) noexcept
{
  hp -= v;

    if(hp <= 0)
    {
      die();
    }
}


void
Player::
receive_hp_recover(int  v) noexcept
{
  hp += v;

    if(hp >= hp_max)
    {
      hp = hp_max;
    }
}


void
Player::
receive_mp_damage(int  v) noexcept
{
  mp -= v;

    if(mp < 0)
    {
      mp = 0;
    }
}


void
Player::
receive_mp_recover(int  v) noexcept
{
  mp += v;

    if(mp > mp_max)
    {
      mp = mp_max;
    }
}




}




