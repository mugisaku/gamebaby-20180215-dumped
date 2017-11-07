#ifndef GMBB_Game_HPP
#define GMBB_Game_HPP


#include"gmbb_Standard.hpp"


namespace gmbb{


Image const&  update_screen() noexcept;

void  initialize() noexcept;

void  step(Controller const&  ctrl);


}




#endif




