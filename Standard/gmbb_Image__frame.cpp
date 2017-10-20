#include"gmbb_Image.hpp"
#include<cstring>




namespace gmbb{


constexpr ColorIndex
palette[] =
{
  predefined_color_index::null,
  predefined_color_index::blue,
  predefined_color_index::white,
  predefined_color_index::light_gray,
};


constexpr uint8_t
top_piece[8][8] =
{
  {0,0,3,3,3,3,3,3},
  {0,3,3,2,2,2,2,2},
  {3,3,2,2,3,3,3,3},
  {3,2,2,3,3,1,1,1},
  {3,2,3,3,1,1,1,1},
  {3,2,3,1,1,1,1,1},
  {3,2,3,1,1,1,1,1},
  {3,2,3,1,1,1,1,1},
};


constexpr uint8_t
bottom_piece[8][8] =
{
  {3,2,3,1,1,1,1,1},
  {3,2,3,1,1,1,1,1},
  {3,2,3,3,1,1,1,1},
  {3,2,2,3,3,1,1,1},
  {3,2,2,2,3,3,3,3},
  {3,3,2,2,2,2,2,2},
  {0,3,3,2,2,2,2,2},
  {0,0,3,3,3,3,3,3},
};


void
Image::
draw_frame_top(int  x, int  y, int  w) noexcept
{
    for(int  yy = 0;  yy < 8;  yy += 1){
    for(int  xx = 0;  xx < 8;  xx += 1){
      auto  v = top_piece[yy][xx];

        if(v)
        {
          draw_dot(Point(x+xx    ,y+yy),palette[v]);
          draw_dot(Point(x+w-1-xx,y+yy),palette[v]);
        }
    }}


  x +=  8;
  w -= 16;

  draw_hline(Point(x,y++),w,palette[3]);
  draw_hline(Point(x,y++),w,palette[2]);
  draw_hline(Point(x,y++),w,palette[3]);
  draw_hline(Point(x,y++),w,palette[1]);
  draw_hline(Point(x,y++),w,palette[1]);
  draw_hline(Point(x,y++),w,palette[1]);
  draw_hline(Point(x,y++),w,palette[1]);
  draw_hline(Point(x,y  ),w,palette[1]);
}


void
Image::
draw_frame_body(int  x, int  y, int  w, int  h) noexcept
{
  draw_vline(Point(x+0,y),h,palette[3]);
  draw_vline(Point(x+1,y),h,palette[2]);
  draw_vline(Point(x+2,y),h,palette[3]);

  draw_vline(Point(x+w-1-0,y),h,palette[3]);
  draw_vline(Point(x+w-1-1,y),h,palette[2]);
  draw_vline(Point(x+w-1-2,y),h,palette[3]);


    while(h--)
    {
      draw_hline(Point(x+3,y++),w-6,palette[1]);
    }
}


void
Image::
draw_frame_bottom(int  x, int  y, int  w) noexcept
{
    for(int  yy = 0;  yy < 8;  yy += 1){
    for(int  xx = 0;  xx < 8;  xx += 1){
      auto  v = bottom_piece[yy][xx];

        if(v)
        {
          draw_dot(Point(x+xx    ,y+yy),palette[v]);
          draw_dot(Point(x+w-1-xx,y+yy),palette[v]);
        }
    }}


  x +=  8;
  w -= 16;

  draw_hline(Point(x,y++),w,palette[1]);
  draw_hline(Point(x,y++),w,palette[1]);
  draw_hline(Point(x,y++),w,palette[1]);
  draw_hline(Point(x,y++),w,palette[1]);
  draw_hline(Point(x,y++),w,palette[3]);
  draw_hline(Point(x,y++),w,palette[2]);
  draw_hline(Point(x,y++),w,palette[2]);
  draw_hline(Point(x,y  ),w,palette[3]);
}


void
Image::
draw_frame(int  x, int  y, int  w, int  h) noexcept
{
  draw_frame_top(   x,y    ,w     );
  draw_frame_body(  x,y  +8,w,h-16);
  draw_frame_bottom(x,y+h-8,w     );
}




}





