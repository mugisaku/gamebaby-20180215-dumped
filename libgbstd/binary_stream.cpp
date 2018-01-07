#include"libgbstd/binary_stream.hpp"
#include"libgbstd/text.hpp"
#include<cstdio>
#include<zlib.h>




namespace gbstd{
namespace binary_streams{




bool
binary_stream::
set_content_from_file(gbstd::string_view  path) noexcept
{
  m_content.clear();

  auto  s = get_string(path);

  auto  gz = gzopen(s,"rb");

    if(gz)
    {
        for(;;)
        {
          auto  c = gzgetc(gz);

            if(gzeof(gz))
            {
              break;
            }


          m_content.push_back(c);
        }


      gzclose(gz);

      return true;
    }

  else
    {
      auto  f = fopen(s,"rb");

        if(f)
        {
            for(;;)
            {
              auto  c = fgetc(f);

                if(feof(f))
                {
                  break;
                }


              m_content.push_back(c);
            }


          fclose(f);

          return true;
        }
    }


  return false;
}




void
binary_stream::
output_content_to_file(gbstd::string_view  path, bool  use_zlib) const noexcept
{
  auto  s = get_string(path);

    if(use_zlib)
    {
      auto  gz = gzopen(s,"wb");

        if(gz)
        {
            for(auto  c: m_content)
            {
              gzputc(gz,c);
            }


          gzclose(gz);
        }
    }

  else
    {
      auto  f = fopen(s,"wb");

        if(f)
        {
            for(auto  c: m_content)
            {
              fputc(c,f);
            }


          fclose(f);
        }
    }
}


}}




