#include"gmbb_Image.hpp"
#include"gmbb_GlyphSet.hpp"
#include"gmbb_unicode.hpp"




namespace gmbb{




void
Image::
print(char16_t  c, Point  pt, GlyphSet const&  glset, ColorIndex const*  coloring) noexcept
{
  auto  p = glset.get_glyph_data(c);

    if(p)
    {
      int  w = glset.get_width();
      int  h = glset.get_height();

      int  bpp = glset.get_bits_per_pixel();

      int  const shift_amount = (bpp == 1)? 31:30;

        for(int  yy = 0;  yy < h;  yy += 1)
        {
          auto   dst = &get_pixel(pt.x,pt.y+yy);
          auto  code = *p++;

            for(int  xx = 0;  xx < w;  xx += 1)
            {
              auto  src = coloring[code>>shift_amount];

                if(src)
                {
                  dst->index = src;
                }


              ++dst;

              code <<= (32-shift_amount);
            }
        }
    }
}




void
Image::
print(const char*  s, Point  pt, GlyphSet const&  glset, ColorIndex const*  coloring) noexcept
{
    while(*s)
    {
      auto  byte_number = utf8_byte_number(*s);

      auto  c = to_char32(s,byte_number);

      s += byte_number;

      print(static_cast<char16_t>(c),pt,glset,coloring);

      pt.x += glset.get_width();
    }
}




void
Image::
print(const char16_t*  s, Point  pt, GlyphSet const&  glset, ColorIndex const*  coloring) noexcept
{
    while(*s)
    {
      print(*s++,pt,glset,coloring);

      pt.x += glset.get_width();
    }
}




}





