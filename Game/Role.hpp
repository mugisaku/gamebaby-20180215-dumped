#ifndef game_Role_HPP
#define game_Role_HPP


#include"gmbb_Standard.hpp"
#include"gmbb_Script.hpp"


namespace gmbb{


struct
TalkAction
{
  std::string  with;

  script::ListNode const*  content;

};


class
Role
{
  std::string  name;

  std::vector<TalkAction>  talk_action_table;

public:
  void  build_from(script::List const&  ls) noexcept;

  script::ListNode const*  find_talk_data(std::string const&  target) const noexcept;

};




}




#endif




