#include"Game_private.hpp"
#include<vector>


namespace gmbb{


namespace{


struct
Element
{
  std::string  guest_name;

  std::string  content;

  Element(std::string const&  guest_name_, std::string const&  content_) noexcept:
  guest_name(guest_name_),
  content(content_){}

};


struct
Talk
{
  std::string  host_name;

  std::vector<Element>  table;

  Talk(std::string const&  host_name_) noexcept:
  host_name(host_name_){}

};


std::vector<Talk>
table;


}


void
push_talk(std::string const&  host_name, std::string const&  guest_name, std::string const&  content) noexcept
{
    for(auto&  t: table)
    {
        if(t.host_name == host_name)
        {
          t.table.emplace_back(guest_name,content);

          return;
        }
    }


  table.emplace_back(host_name);

  table.back().table.emplace_back(guest_name,content);
}


void
clear_all_talk() noexcept
{
  table.clear();
}


std::string const*
find_talk(std::string const&  host_name, std::string const&  guest_name) noexcept
{
    for(auto&  t: table)
    {
        if(t.host_name == host_name)
        {
            for(auto&  e: t.table)
            {
                if(e.guest_name == guest_name)
                {
                  return &e.content;
                }
            }


          return nullptr;
        }
    }


  return nullptr;
}


}




