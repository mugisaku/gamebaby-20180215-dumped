#ifndef GMBB_Game_HPP
#define GMBB_Game_HPP


#include"gmbb_Standard.hpp"


namespace gmbb{


Image const&  get_screen_image() noexcept;

void  initialize() noexcept;

void  step(Controller const&  ctrl);


}




#endif




