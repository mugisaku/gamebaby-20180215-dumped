#include"gmbb_Stream.hpp"
#include<cstdio>
#include<zlib.h>




namespace gmbb{




Stream::
Stream(StreamReader&  r) noexcept
{
  auto  len = r.get_be32();
std::string  name;
  name.resize(len);

  auto  it = name.begin();

    while(len--)
    {
      *it++ = r.get();
    }


  len = r.get_be32();

  content.resize(len);

  it = content.begin();

    while(len--)
    {
      *it++ = r.get();
    }
}




bool
Stream::
set_content_from_file(const char*  path) noexcept
{
  content.clear();

  auto  gz = gzopen(path,"rb");

    if(gz)
    {
        for(;;)
        {
          auto  c = gzgetc(gz);

            if(gzeof(gz))
            {
              break;
            }


          content.push_back(c);
        }


      gzclose(gz);

      return true;
    }

  else
    {
      auto  f = fopen(path,"rb");

        if(f)
        {
            for(;;)
            {
              auto  c = fgetc(f);

                if(feof(f))
                {
                  break;
                }


              content.push_back(c);
            }


          fclose(f);

          return true;
        }
    }


  return false;
}




void
Stream::
output_content_to_file(const char*  path, bool  use_zlib) const noexcept
{
    if(use_zlib)
    {
      auto  gz = gzopen(path,"wb");

        if(gz)
        {
            for(auto  c: content)
            {
              gzputc(gz,c);
            }


          gzclose(gz);
        }
    }

  else
    {
      auto  f = fopen(path,"wb");

        if(f)
        {
            for(auto  c: content)
            {
              fputc(c,f);
            }


          fclose(f);
        }
    }
}


}




