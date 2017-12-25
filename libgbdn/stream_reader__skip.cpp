#include"stream_reader.hpp"
#include<cstring>




namespace gbdn{


void
stream_reader::
skip_linestyle_comment()
{
    for(;;)
    {
      auto  c = *m_pointer;

        if(!c)
        {
          break;
        }

      else           
        if(c == '\n')
        {
          ++m_pointer;

          newline();

          break;
        }

      else
        {
          ++m_pointer;
        }           
    }
}


void
stream_reader::
skip_blockstyle_comment()
{
    for(;;)
    {
      auto  c = *m_pointer;

        if(!c)
        {
          throw stream_error(*this,"ブロック式コメントが閉じられていない");
        }

      else           
        if(c == '*')
        {
          ++m_pointer;

            if(*m_pointer == '/')
            {
              ++m_pointer;

              break;
            }
        }

      else           
        if(c == '\n')
        {
          ++m_pointer;

          newline();
        }

      else
        {
          ++m_pointer;
        }           
    }
}


void
stream_reader::
skip_spaces() noexcept
{
    for(;;)
    {
      auto  c = *m_pointer;

        if((c ==  ' ') ||
           (c == '\t') ||
           (c == '\r') ||
           (c == '\v'))
        {
          ++m_pointer;
        }

      else           
        if(c == '\n')
        {
          ++m_pointer;

          newline();
        }

      else           
        if(c == '/')
        {
          c = *(m_pointer+1);

            if(c == '*')
            {
              m_pointer += 2;

              skip_blockstyle_comment();
            }

          else
            if(c == '/')
            {
              m_pointer += 2;

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




