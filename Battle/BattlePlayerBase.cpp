#include"BattlePlayerBase.hpp"
#include"ReadOnlyData.hpp"




void
PlayerBase::
load(gbstd::string_view  name, const gbdn::list&  ls)
{
  m_name = name;
  m_body_strength = ls.get_named_value("body_strength").get_integer();
  m_mind_strength = ls.get_named_value("mind_strength").get_integer();
  m_agility       = ls.get_named_value("agility").get_integer();
  m_defense       = ls.get_named_value("defense").get_integer();
  m_intellect     = ls.get_named_value("intellect").get_integer();
  m_hp            = ls.get_named_value("hp").get_integer();
  m_mp            = ls.get_named_value("mp").get_integer();


 auto  cmd = &m_command_table.commands[0];

    for(auto&  v: ls.get_named_value("command_table").get_list())
    {
      auto&  s = v.get_string();

      *cmd++ = &ro::get_command(s.get_view());
    }
}


void
PlayerBase::
print() const noexcept
{
  printf("%s:{\n",m_name.data());
  printf("body_strngth:%d\n",m_body_strength);
  printf("mind_strngth:%d\n",m_mind_strength);
  printf("agility:%d\n",m_agility);
  printf("defense:%d\n",m_defense);
  printf("intellect:%d\n",m_intellect);
  printf("hp:%d\n",m_hp);
  printf("mp:%d\n",m_mp);
}




