#include"ShopManager.hpp"
#include<list>




namespace gmbb{


namespace{
std::list<covered_ptr<Shop>>
list;
}


void
push_shop(Shop&  shop) noexcept
{
  list.emplace_back(&shop);
}


void
push_shop_from_script(script::ListNode const*  cur) noexcept
{
}


covered_ptr<Shop>
find_shop(std::string const&  name) noexcept
{
    for(auto  ptr: list)
    {
        if(ptr->get_name() == name)
        {
          return ptr;
        }
    }


  return nullptr;
}


int
get_number_of_shops() noexcept
{
  return list.size();
}


}




