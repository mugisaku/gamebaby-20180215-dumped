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


namespace{
int
clamp(int  n) noexcept
{
  return (n <= 0)? 0:
         (n >= 7)? 7:n;
}
}


void
Image::
add(int  r, int  g, int  b) noexcept
{
    for(auto&  pix: pixels)
    {
        if(pix.index)
        {
          auto  new_r = clamp(pix.index.r()+r);
          auto  new_g = clamp(pix.index.g()+g);
          auto  new_b = clamp(pix.index.b()+b);

          pix.index = ColorIndex(new_r,new_g,new_b);
        }
    }
}


void
Image::
reverse_color() noexcept
{
    for(auto&  pix: pixels)
    {
        if(pix.index)
        {
          auto  new_r = (7-pix.index.r());
          auto  new_g = (7-pix.index.g());
          auto  new_b = (7-pix.index.b());

          pix.index = ColorIndex(new_r,new_g,new_b);
        }
    }
}


}





