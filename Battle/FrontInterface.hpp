#ifndef GMBB_FrontInterFace_HPP
#define GMBB_FrontInterFace_HPP


#include"libgbstd/image.hpp"
#include"Screen.hpp"


const gbstd::image&  update_screen() noexcept;

void  initialize() noexcept;

void  step();




#endif




