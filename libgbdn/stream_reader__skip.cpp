#include"stream_reader.hpp"
#include<cstring>




namespace gbdn{


void
stream_reader::
skip_linestyle_comment()
{
    for(;;)
    {
      auto  c = *pointer;

        if(!c)
        {
          break;
        }

      else           
        if(c == '\n')
        {
          ++pointer;

          newline();

          break;
        }

      else
        {
          ++pointer;
        }           
    }
}


void
stream_reader::
skip_blockstyle_comment()
{
    for(;;)
    {
      auto  c = *pointer;

        if(!c)
        {
          throw stream_error(*this,"ブロック式コメントが閉じられていない");
        }

      else           
        if(c == '*')
        {
          ++pointer;

            if(*pointer == '/')
            {
              ++pointer;

              break;
            }
        }

      else           
        if(c == '\n')
        {
          ++pointer;

          newline();
        }

      else
        {
          ++pointer;
        }           
    }
}


void
stream_reader::
skip_spaces() noexcept
{
    for(;;)
    {
      auto  c = *pointer;

        if((c ==  ' ') ||
           (c == '\t') ||
           (c == '\r') ||
           (c == '\v'))
        {
          ++pointer;
        }

      else           
        if(c == '\n')
        {
          ++pointer;

          newline();
        }

      else           
        if(c == '/')
        {
          c = *(pointer+1);

            if(c == '*')
            {
              pointer += 2;

              skip_blockstyle_comment();
            }

          else
            if(c == '/')
            {
              pointer += 2;

              skip_linestyle_comment();
            }

          else
            {
              break;
            }
        }

      else
        {
          break;
        }           
    }
}


}




