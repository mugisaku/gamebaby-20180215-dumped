#include"Role.hpp"
#include"ScriptManager.hpp"




namespace gmbb{


using namespace script;


void
Role::
build_from(List const&  ls) noexcept
{
    for(auto&  v: ls)
    {
        if(v.is_list("talk_action"))
        {
          auto&  lsls = v.get_list();

          auto&   target = lsls.get_string("with");
          auto&  content = lsls["content"];

            if(content.is_string())
            {
              talk_action_table.emplace_back(content.get_string(),target);
            }
        }
    }
}


TalkAction const*
Role::
find_talk_action(std::string const&  target) const noexcept
{
    for(auto&  tka: talk_action_table)
    {
        if(tka.with == target)
        {
          return &tka;
        }
    }


  return nullptr;
}




}




