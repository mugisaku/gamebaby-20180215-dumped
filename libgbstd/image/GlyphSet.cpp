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


namespace{
void
load(uint32_t*  ln, int  h, int  line_size, StreamReader&  r)
{
    for(int  i = 0;  i < h;  ++i)
    {
      uint32_t   v;

        if(line_size <= 8)
        {
          v = r.get()<<24;
        }

      else
        if(line_size <= 16)
        {
          v = r.get_be16()<<16;
        }

      else
        {
          v = r.get_be32();
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
load_from_file(char const*  path) noexcept
{
  Stream  s;

    if(s.set_content_from_file(path))
    {
      auto  r = s.make_reader();

      load_from_stream(r);
    }
}


void
GlyphSet::
load_from_stream(StreamReader&  r) noexcept
{
  clear();

  this->width          = r.get();
  this->height         = r.get();
  this->bits_per_pixel = r.get();

  int  const line_size = this->bits_per_pixel*this->width;

  auto  n = r.get_be16();

    while(n--)
    {
      auto  unicode = r.get_be16();

        if(unicode >= 0xFF00)
        {
          unicode -= 0xFF00-' ';
        }


      auto&  ln = this->link_table[unicode];

        if(!ln)
        {
          ln = new uint32_t[this->height];
        }


      load(ln,this->height,line_size,r);
    }
}




void
GlyphSet::
save_to_file(char const*  path) const noexcept
{
  Stream  s;

  StreamWriter  w(&s);

  save_to_stream(w);

  s.output_content_to_file(path);
}


void
GlyphSet::
save_to_stream(StreamWriter&  w) const noexcept
{
  auto&  bpp = this->bits_per_pixel;

  int  const line_size = 2*this->width;

  w.put(this->width);
  w.put(this->height);
  w.put(2);

  auto  off = w.get_offset();

  w.put_be16(0);


  int  n = 0;

  int  unicode = 0;

    for(auto  ln: link_table)
    {
        if(ln)
        {
          ++n;

          w.put_be16(unicode);

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


                       if(line_size <=  8){w.put(     v);}
                  else if(line_size <= 16){w.put_be16(v);}
                  else                    {w.put_be32(v);}
                }
            }

          else
            {
                for(int  y = 0;  y < this->height;  ++y)
                {
                  w.put_be32(ln[y]);
                }
            }
        }


      ++unicode;
    }


  w.set_offset(off);

  w.put_be16(n);
}


}




