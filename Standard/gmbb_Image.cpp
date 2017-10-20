#include"gmbb_Image.hpp"
#include<cstring>



namespace gmbb{




Image::
Image(int  w, int  h) noexcept
{
  resize(w,h);
}




void
Image::
resize(int  w, int  h) noexcept
{
  width  = w;
  height = h;

  pixels.resize(w*h);

  fill();
}




uint32_t
Image::
get_pixel_color(int  x, int  y, Palette const&  pal) const noexcept
{
  return pal.get_color(get_const_pixel(x,y).index);
}


void
Image::
fill(Pixel  pix) noexcept
{
  std::fill(this->pixels.begin(),this->pixels.end(),pix);
}




}





