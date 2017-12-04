#include"gamn_StreamReader.hpp"
#include<cstring>




namespace gamn{


void
StreamReader::
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
StreamReader::
skip_blockstyle_comment()
{
    for(;;)
    {
      auto  c = *pointer;

        if(!c)
        {
          throw StreamError(*this,"ブロック式コメントが閉じられていない");
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
StreamReader::
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




