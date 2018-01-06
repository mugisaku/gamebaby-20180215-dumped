#include"BattleCommand.hpp"




extern std::initializer_list<Process>
process_list;


namespace{


TargetKind
to_target(const gbdn::string&  s) noexcept
{
       if(s == std::string_view("null"                )){return TargetKind::null;}
  else if(s == std::string_view("self"                )){return TargetKind::self;}
  else if(s == std::string_view("one_of_own_team"     )){return TargetKind::one_of_own_team;}
  else if(s == std::string_view("all_of_own_team"     )){return TargetKind::all_of_own_team;}
  else if(s == std::string_view("one_of_opposite_team")){return TargetKind::one_of_opposite_team;}
  else if(s == std::string_view("all_of_opposite_team")){return TargetKind::all_of_opposite_team;}
  else if(s == std::string_view("all_of_both_team"    )){return TargetKind::all_of_both_team;}

  return TargetKind::null;
}


const Process&
get_process(std::string_view  name) noexcept
{
    for(auto&  proc: process_list)
    {
        if(proc.name == name)
        {
          return proc;
        }
    }


  printf("%sというプロセスはない\n",name.data());
}


}


void
BattleCommand::
load(const gbdn::list&  ls)
{
  m_strength = ls.get_named_value("strength").get_integer();
  m_weight   = ls.get_named_value("weight").get_integer();

  m_effect_process = &get_process(ls.get_named_value("effect").get_string().get_view());
  m_action_process = &get_process(ls.get_named_value("action").get_string().get_view());

  m_target_kind = to_target(ls.get_named_value("target").get_string());
}




