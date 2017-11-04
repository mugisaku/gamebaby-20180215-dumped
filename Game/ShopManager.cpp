#include"ShopManager.hpp"
#include"ScriptManager.hpp"
#include<list>
#include<memory>




namespace gmbb{


namespace{
std::list<std::unique_ptr<Shop>>
list;


covered_ptr<Shop>
current;


}


void
reset_shops() noexcept
{
  list.clear();

  auto  mod = find_script("shop");

    if(mod && mod->is_list())
    {
        for(auto&  v: mod->get_list())
        {
            if(v.is_list())
            {
              list.emplace_back(new Shop(v.get_name(),v.get_list()));
            }
        }
    }
}


covered_ptr<Shop>
find_shop(std::string const&  name) noexcept
{
    for(auto&  ptr: list)
    {
        if(ptr->get_name() == name)
        {
          return ptr.get();
        }
    }


  return nullptr;
}


covered_ptr<Shop>
change_current_shop(std::string const&  name) noexcept
{
         current = find_shop(name);
  return current                  ;
}


covered_ptr<Shop>
get_current_shop() noexcept
{
  return current;
}


int
get_number_of_shops() noexcept
{
  return list.size();
}


}




