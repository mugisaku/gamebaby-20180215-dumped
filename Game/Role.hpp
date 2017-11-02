#ifndef game_Role_HPP
#define game_Role_HPP


#include"gmbb_Standard.hpp"
#include"gmbb_Script.hpp"


namespace gmbb{


struct
TalkAction
{
  std::string const&  label;
  std::string const&   with;

  TalkAction(std::string const&  label_, std::string const&  with_):
  label(label_),
  with(with_)
  {}

};


class
Role
{
  std::string  name;

  std::vector<TalkAction>  talk_action_table;

public:
  void  build_from(script::List const&  ls) noexcept;

  TalkAction const*  find_talk_action(std::string const&  target) const noexcept;

};




}




#endif




