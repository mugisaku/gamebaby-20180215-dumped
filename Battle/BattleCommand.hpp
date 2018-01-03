#ifndef BattleCommand_HPP
#define BattleCommand_HPP


#include"libgbdn/gbdn.hpp"
#include<string>


enum class
TargetKind
{
  null,
  self,
  one_of_own_team,
  all_of_own_team,
  one_of_opposite_team,
  all_of_opposite_team,
  all_of_both_team,

};


enum class
ActionKind
{
  null,
  attack,
  use,

};


enum class
EffectKind
{
  null,
  hp_damage,
  hp_recover,

};


enum class
AbilityKind
{
  null,
  
};


class
BattleCommand
{
  std::string  m_name;

  int  m_strength=0;
  int    m_weight=0;

  TargetKind  m_target_kind=TargetKind::null;
  ActionKind  m_action_kind=ActionKind::null;
  EffectKind  m_effect_kind=EffectKind::null;

public:
  BattleCommand() noexcept{}
  BattleCommand(std::string_view  name, const gbdn::list&  ls){load(name,ls);}

  void                set_name(std::string_view  name)       noexcept{       m_name = name;}
  const std::string&  get_name(                      ) const noexcept{return m_name       ;}

  int  get_strength() const noexcept{return m_strength;}
  int  get_weight() const noexcept{return m_weight;}

  TargetKind  get_target_kind() const noexcept{return m_target_kind;}
  ActionKind  get_action_kind() const noexcept{return m_action_kind;}
  EffectKind  get_effect_kind() const noexcept{return m_effect_kind;}

  void  load(std::string_view  name, const gbdn::list&  ls);

};


struct
CommandTable
{
  static constexpr int  number_of_commands = 4;

  BattleCommand  commands[number_of_commands];

};




#endif




