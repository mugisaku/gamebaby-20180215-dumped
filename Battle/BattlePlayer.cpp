#include"BattlePlayer.hpp"
#include"gmbb_unicode.hpp"


namespace gmbb{




void
Player::
set_data(const Enemy&  ene) noexcept
{
  kind = PlayerKind::enemy;

  data.enemy = &ene;

  static_cast<PlayerBase&>(*this) = ene;
}


void
Player::
set_data(Hero&  hro) noexcept
{
  kind = PlayerKind::hero;

  data.hero = &hro;

  static_cast<PlayerBase&>(*this) = hro;
}


void
Player::
unset_data() noexcept
{
  kind = PlayerKind::null;
}




int
Player::
calculate_hp_max() const noexcept
{
  return 20+(body_strength*2)+(expset.damage/16);
}


int
Player::
calculate_mp_max() const noexcept
{
  return(mind_strength*2)+(expset.magic/16);
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
  hp_max = calculate_hp_max();
  mp_max = calculate_mp_max();

  attack_strength = calculate_attack_strength();
  guard_strength = calculate_guard_strength();
  magic_strength = calculate_magic_strength();

  number_of_attacks = calculate_number_of_attacks();
  number_of_guards = calculate_number_of_guards();
  number_of_magics = calculate_number_of_magics();
}




}




