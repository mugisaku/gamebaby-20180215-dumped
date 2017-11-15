#ifndef GMBB_GameData_HPP
#define GMBB_GameData_HPP


#include"gmbb_Standard.hpp"
#include"Screen.hpp"
#include"GameItem.hpp"


namespace gmbb{


constexpr int  square_size = 24;

constexpr int  board_width  = 14;
constexpr int  board_height = 14;

constexpr int  board_image_width  = square_size*board_width ;
constexpr int  board_image_height = square_size*board_height;


extern Image  character_image;


Rectangle  get_rectangle_for_item(GameItem const&  itm) noexcept;


struct
PickUpParameter
{
  covered_ptr<GameItem>  dst;
  covered_ptr<GameItem>  src;

};

extern PickUpParameter   pickup_parameter;


}




#endif




