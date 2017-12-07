#include"BattlePlayerBase.hpp"


namespace gmbb{


void
PlayerBase::
load(const char*  name_, const gbdn::list&  ls)
{
  name = name_;
  body_strength = ls.get_named_value("body_strength").get_integer();
  mind_strength = ls.get_named_value("mind_strength").get_integer();
  agility       = ls.get_named_value("agility").get_integer();
  defense       = ls.get_named_value("defense").get_integer();
  intellect     = ls.get_named_value("intellect").get_integer();
  hp            = ls.get_named_value("hp").get_integer();
  mp            = ls.get_named_value("mp").get_integer();


 auto  cmd = make_rw(command_table.commands[0]);

    for(auto&  v: ls.get_named_value("command_table").get_list())
    {
      cmd++->name = v.get_string().get_data();
    }
}


void
PlayerBase::
print() const noexcept
{
  printf("%s:{\n",name.data());
  printf("body_strngth:%d\n",body_strength);
  printf("mind_strngth:%d\n",mind_strength);
  printf("agility:%d\n",agility);
  printf("defense:%d\n",defense);
  printf("intellect:%d\n",intellect);
  printf("hp:%d\n",hp);
  printf("mp:%d\n",mp);
}


}




