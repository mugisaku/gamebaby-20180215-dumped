#ifndef game_ShopManager_HPP
#define game_ShopManager_HPP


#include"Shop.hpp"
#include"covered_ptr"


namespace gmbb{


void  push_shop(Shop&  shop) noexcept;
void  push_shop_from_script(script::ListNode const*  cur) noexcept;

covered_ptr<Shop>  find_shop(std::string const&  name) noexcept;

int  get_number_of_shops() noexcept;


}




#endif




