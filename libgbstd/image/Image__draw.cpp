#include"gmbb_Image.hpp"
#include"gmbb_LineMaker.hpp"
#include<cstring>



namespace gmbb{




void
Image::
draw_dot(Point  pt, ColorIndex  i) noexcept
{
    if(i)
    {
      this->pixels[(this->width*pt.y)+pt.x].index = i;
    }
}


void
Image::
draw_dot_safely(Point  pt, ColorIndex  i) noexcept
{
    if((pt.x >=            0) &&
       (pt.x <   this->width) &&
       (pt.y >=            0) &&
       (pt.y <  this->height))
    {
      draw_dot(pt,i);
    }
}


void
Image::
draw_dot(Point  pt, Pixel  pix) noexcept
{
    if(pix.index)
    {
      auto&  dst = this->pixels[(this->width*pt.y)+pt.x];

        if(dst.z <= pix.z)
        {
          dst = pix;
        }
    }
}


void
Image::
draw_dot_safely(Point  pt, Pixel  pix) noexcept
{
    if((pt.x >=            0) &&
       (pt.x <   this->width) &&
       (pt.y >=            0) &&
       (pt.y <  this->height))
    {
      draw_dot(pt,pix);
    }
}


void
Image::
draw_vline(Point  pt, int  l, Pixel  pix) noexcept
{
    while(l--)
    {
      draw_dot(pt,pix);

      pt.y += 1;
    }
}


void
Image::
draw_vline_safely(Point  pt, int  l, Pixel  pix) noexcept
{
    if((pt.x >=     0) &&
       (pt.x <  width))
    {
        if(pt.y < 0)
        {
          l += pt.y    ;
               pt.y = 0;
        }

      else
        if(pt.y+l >= height)
        {
          l = height-pt.y;
        }


        if(l > 0)
        {
            while(l--)
            {
              draw_dot(pt,pix);

              pt.y += 1;
            }
        }
    }
}


void
Image::
draw_hline(Point  pt, int  l, Pixel  pix, int  interval) noexcept
{
  int  n = interval;

    while(l--)
    {
        if(n)
        {
          --n;
        }

      else
        {
          draw_dot(pt,pix);

          n = interval;
        }


      pt.x += 1;
    }
}


void
Image::
draw_hline_safely(Point  pt, int  l, Pixel  pix) noexcept
{
    if((pt.y >=      0) &&
       (pt.y <  height))
    {
        if(pt.x < 0)
        {
          l += pt.x    ;
               pt.x = 0;
        }

      else
        if(pt.x+l >= width)
        {
          l = width-pt.x;
        }


        if(l > 0)
        {
            while(l--)
            {
              draw_dot(pt,pix);

              pt.x += 1;
            }
        }
    }
}


void
Image::
draw_line(Line  line, Pixel  pix) noexcept
{
  LineMaker  lnmk(line);

  draw_dot(lnmk.get_point(),pix);

    while(lnmk.get_distance())
    {
      lnmk.step();

      draw_dot(lnmk.get_point(),pix);
    }
}


void
Image::
draw_rectangle(Rectangle const&  rect, Pixel  pix) noexcept
{
  draw_hline(Point(rect.x,rect.y         ),rect.w,pix);
  draw_hline(Point(rect.x,rect.y+rect.h-1),rect.w,pix);

  draw_vline(Point(rect.x         ,rect.y+1),rect.h-2,pix);
  draw_vline(Point(rect.x+rect.w-1,rect.y+1),rect.h-2,pix);
}


void
Image::
draw_rectangle_safely(Rectangle const&  rect, Pixel  pix) noexcept
{
  draw_hline_safely(Point(rect.x,rect.y         ),rect.w,pix);
  draw_hline_safely(Point(rect.x,rect.y+rect.h-1),rect.w,pix);

  draw_vline_safely(Point(rect.x         ,rect.y+1),rect.h-2,pix);
  draw_vline_safely(Point(rect.x+rect.w-1,rect.y+1),rect.h-2,pix);
}


void
Image::
fill_rectangle(Rectangle  rect, Pixel  pix) noexcept
{
    while(rect.h--)
    {
      draw_hline(rect,rect.w,pix);

      ++rect.y;
    }
}


}





