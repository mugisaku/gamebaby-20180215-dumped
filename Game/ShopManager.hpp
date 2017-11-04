#ifndef game_ShopManager_HPP
#define game_ShopManager_HPP


#include"Shop.hpp"
#include"covered_ptr"


namespace gmbb{


void  reset_shops() noexcept;


covered_ptr<Shop>  find_shop(std::string const&  name) noexcept;

covered_ptr<Shop>  change_current_shop(std::string const&  name) noexcept;
covered_ptr<Shop>     get_current_shop() noexcept;

int  get_number_of_shops() noexcept;


}




#endif




