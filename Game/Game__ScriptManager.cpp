#include"Game_private.hpp"
#include<unordered_map>


namespace gmbb{


using namespace script;


namespace{

std::unordered_map<std::string,TokenString const*>
map;


}


Token const*
find_routine(std::string const&  name) noexcept
{
  auto  res = map.find(name);

    if(res != map.cend())
    {
      return res->second->data();
    }


  return nullptr;
}


void
open_script(char const*  filepath) noexcept
{
  auto  s = make_string_from_file(filepath);

  StreamReader  r(s.data());

  TokenString*  toks;

    try
    {
      toks = new TokenString(r);
    }


    catch(StreamError const&  err)
    {
      err.print();

      return;
    }


    if(toks)
    {
      auto   it = toks->cbegin();
      auto  end = toks->cend();

        while(it != end)
        {
            if(*it == TokenKind::identifier)
            {
              std::string const&  name = (*it++).get_string();

                if(*it == TokenKind::token_string)
                {
                  map.emplace(name,&(*it++).get_token_string());
                }
            }

          else
            {
              ++it;
            }
        }
    }
}


}




