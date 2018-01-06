#ifndef BattleCommand_HPP
#define BattleCommand_HPP


#include"libgbdn/gbdn.hpp"
#include<string>




class Player;
class BattleCommand;


using ProcessCallback = void  (*)(Player&  actor, const BattleCommand&  command, Player&  target) noexcept;

struct
Process
{
  std::string_view  name;

  ProcessCallback  callback;

};


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


class
BattleCommand
{
  std::string  m_name;

  int  m_strength=0;
  int    m_weight=0;

  TargetKind  m_target_kind=TargetKind::null;

  const Process*  m_action_process=nullptr;
  const Process*  m_effect_process=nullptr;

public:
  BattleCommand() noexcept{}
  BattleCommand(const gbdn::list&  ls){load(ls);}

  void                set_name(std::string_view  name)       noexcept{       m_name = name;}
  const std::string&  get_name(                      ) const noexcept{return m_name       ;}

  int  get_strength() const noexcept{return m_strength;}
  int  get_weight() const noexcept{return m_weight;}

  TargetKind  get_target_kind() const noexcept{return m_target_kind;}

  const Process*  get_action_process() const noexcept{return m_action_process;}
  const Process*  get_effect_process() const noexcept{return m_effect_process;}

  void  load(const gbdn::list&  ls);

};


struct
CommandTable
{
  static constexpr int  number_of_commands = 4;

  const BattleCommand*  commands[number_of_commands] = {0};

};




#endif




