#include"gmbb_GlyphSet.hpp"




namespace gmbb{


void
GlyphSet::
clear() noexcept
{
    for(auto&  ln: this->link_table)
    {
      delete[] ln          ;
               ln = nullptr;
    }


  this->width  = 0;
  this->height = 0;
}




uint32_t const*
GlyphSet::
get_glyph_data(char16_t  c) const noexcept
{
  return this->link_table[(c < 0xFF00)? c:(c-0xFF00+' ')];
}


void
GlyphSet::
load_from_file(char const*  path) noexcept
{
  auto  f = fopen(path,"rb");

    if(f)
    {
      load_from_file(f);

      fclose(f);
    }
}


namespace{
void
fputc_u16be(uint16_t  c, FILE*  f) noexcept
{
  fputc(c>>8,f);
  fputc(c   ,f);
}


void
fputc_u32be(uint32_t  c, FILE*  f) noexcept
{
  fputc(c>>24,f);
  fputc(c>>16,f);
  fputc(c>> 8,f);
  fputc(c    ,f);
}


uint16_t
fgetc_u16be(FILE*  f) noexcept
{
  uint16_t  c  = fgetc(f)<<8;
            c |= fgetc(f)   ;

  return c;
}


uint32_t
fgetc_u32be(FILE*  f) noexcept
{
  uint32_t  c  = fgetc(f)<<24;
            c |= fgetc(f)<<16;
            c |= fgetc(f)<< 8;
            c |= fgetc(f)    ;

  return c;
}


void
load(uint32_t*  ln, int  h, int  line_size, FILE*  f)
{
    for(int  i = 0;  i < h;  ++i)
    {
      uint32_t   v;

        if(line_size <= 8)
        {
          v = fgetc(f)<<24;
        }

      else
        if(line_size <= 16)
        {
          v = fgetc_u16be(f)<<16;
        }

      else
        {
          v = fgetc_u32be(f);
        }


        if(ln)
        {
          ln[i] = v;
        }
    }
}


}


void
GlyphSet::
load_from_file(FILE*  f) noexcept
{
  clear();

  this->width          = fgetc(f);
  this->height         = fgetc(f);
  this->bits_per_pixel = fgetc(f);

  int  const line_size = this->bits_per_pixel*this->width;

  auto  n = fgetc_u16be(f);

    while(n--)
    {
      auto  unicode = fgetc_u16be(f);

        if(unicode >= 0xFF00)
        {
          unicode -= 0xFF00-' ';
        }


      auto&  ln = this->link_table[unicode];

        if(!ln)
        {
          ln = new uint32_t[this->height];
        }


      load(ln,this->height,line_size,f);
    }
}




void
GlyphSet::
save_to_file(char const*  path) const noexcept
{
  auto  f = fopen(path,"wb");

    if(f)
    {
      save_to_file(f);

      fclose(f);
    }
}


void
GlyphSet::
save_to_file(FILE*  f) const noexcept
{
  auto&  bpp = this->bits_per_pixel;

  int  const line_size = 2*this->width;

  fputc(this->width,f);
  fputc(this->height,f);
  fputc(2,f);

  fpos_t  pos;

  fgetpos(f,&pos);

  fputc_u16be(0,f);


  int  n = 0;

  int  unicode = 0;

    for(auto  ln: link_table)
    {
        if(ln)
        {
          ++n;

          fputc_u16be(unicode,f);

            if(bpp == 1)
            {
              int  table[16][16] = {0};

                for(int  i = 0;  i < this->height;  ++i)
                {
                  auto  v = ln[i];

                    for(int  x = 0;  x < this->width;  ++x)
                    {
                      table[i][x] = (v>>31);

                      v <<= 1;
                    }
                }


                for(int  y = 0;  y < 16;  ++y){
                for(int  x = 0;  x < 16;  ++x){
                  auto  v = table[y][x];

                    if(v == 1)
                    {
                        if((x     ) && !table[y  ][x-1]){table[y  ][x-1] = 2;}
                        if((y     ) && !table[y-1][x  ]){table[y-1][x  ] = 2;}
                        if((x < 15) && !table[y  ][x+1]){table[y  ][x+1] = 2;}
                        if((y < 15) && !table[y+1][x  ]){table[y+1][x  ] = 2;}
                    }
                }}


                for(int  y = 0;  y < this->height;  ++y)
                {
                  uint32_t  v = 0;

                    for(int  x = 0;  x < this->width;  ++x)
                    {
                      v <<= 2;
                      v  |= table[y][x];
                    }


                       if(line_size <=  8){fputc(      v,f);}
                  else if(line_size <= 16){fputc_u16be(v,f);}
                  else                    {fputc_u32be(v,f);}
                }
            }

          else
            {
                for(int  y = 0;  y < this->height;  ++y)
                {
                  fputc_u32be(ln[y],f);
                }
            }
        }


      ++unicode;
    }


  fsetpos(f,&pos);

  fputc_u16be(n,f);
}


}




