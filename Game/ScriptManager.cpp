#include"ScriptManager.hpp"
#include"ShopManager.hpp"
#include"gmbb_Stream.hpp"
#include"Messembly_ImageBuilder.hpp"
#include<vector>
#include<cstring>


namespace gmbb{


using namespace gamn;


namespace{


std::vector<List*>
list_table;


messembly::Image
image;


}




bool
reset_machine(messembly::Machine&  m, const char*  entry_name) noexcept
{
  return m.reset(image,entry_name);
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
  gmbb::Stream  s;

  s.set_content_from_file(filepath);

  gamn::StreamReader  r(s.get_content().data());

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

        for(auto&  v: *ls)
        {
            if(v.is_list("message"))
            {
              messembly::ImageBuilder  builder;

              builder.push_entry_list(v.get_list());

              builder.finalize();

              image = builder.build();
            }
        }
    }
}


}




