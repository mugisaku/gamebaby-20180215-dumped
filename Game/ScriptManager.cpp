#include"ScriptManager.hpp"
#include"ShopManager.hpp"
#include<vector>
#include<cstring>


namespace gmbb{


using namespace gamn;


namespace{


std::vector<List*>
list_table;


}




gamn::Value const*
find_script(char const*  module_name) noexcept
{
    for(auto  ls: list_table)
    {
        for(auto&  mod: *ls)
        {
            if(mod.is_list(module_name))
            {
              return &mod;
            }
        }
    }


  return nullptr;
}


gamn::Value const*
find_script(char const*  module_name, char const*  value_name) noexcept
{
    for(auto  ls: list_table)
    {
        for(auto&  mod: *ls)
        {
            if(mod.is_list(module_name))
            {
                for(auto&  v: mod.get_list())
                {
                    if(v.get_name() == value_name)
                    {
                      return &v;
                    }
                }
            }
        }
    }


  return nullptr;
}


void
load_script_file(char const*  filepath) noexcept
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
      list_table.emplace_back(ls);
    }
}


}




