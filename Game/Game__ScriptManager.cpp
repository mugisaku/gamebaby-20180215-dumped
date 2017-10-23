#include"Game_private.hpp"
#include<unordered_map>


namespace gmbb{


using namespace script;


namespace{


std::unordered_map<std::string,ListNode const*>
routine_map;


std::unordered_map<std::string,ListNode const*>
talk_map;


}


ListNode const*
find_routine(std::string const&  name) noexcept
{
  auto  res = routine_map.find(name);

    if(res != routine_map.cend())
    {
      return res->second;
    }


  return nullptr;
}


void
open_script(char const*  filepath) noexcept
{
  auto  s = make_string_from_file(filepath);

  StreamReader  r(s.data());

  List*  ls;

    try
    {
      ls = new List(r);
    }


    catch(StreamError const&  err)
    {
      err.print();

      return;
    }


    if(ls)
    {
      auto  current = ls->get_first();

        while(current)
        {
          static std::string const  routine_s("routine");
          static std::string const     talk_s("talk");

          auto&  v = current->value;

          current = current->next;

            if(v.is_value(routine_s))
            {
              auto&  vv = v.get_value();

              routine_map.emplace(vv.get_name(),vv.get_list().get_first());
            }

          else
            if(v.is_value(talk_s))
            {
              auto&  vv = v.get_value();

              talk_map.emplace(vv.get_name(),vv.get_list().get_first());
            }
        }
    }
}


}




