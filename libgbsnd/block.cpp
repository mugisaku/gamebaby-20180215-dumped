#include"libgbsnd/stmt.hpp"


namespace gbsnd{
namespace devices{


block::
block(tok::stream_reader&  r) noexcept
{
    for(;;)
    {
      r.skip_spaces();

        if(r.is_reached_end())
        {
          break;
        }

      else
        if(r.is_pointing_identifier())
        {
          auto  id = r.read_identifier();

               if(id == gbstd::string_view("return")){}
          else if(id == gbstd::string_view("while")){}
          else if(id == gbstd::string_view("if")){}
          else if(id == gbstd::string_view("for")){}
          else if(id == gbstd::string_view("switch")){}
          else if(id == gbstd::string_view("case")){}
          else if(id == gbstd::string_view("goto")){}
          else if(id == gbstd::string_view("default")){}
          else if(id == gbstd::string_view("break")){}
          else if(id == gbstd::string_view("continue")){}
          else if(id == gbstd::string_view("true")){}
          else if(id == gbstd::string_view("false")){}
        }

      else
        if(r.is_pointing_number())
        {
        }

      else
        {
          auto  c = r.get_char();

            if(c == '(')
            {
              r.advance();
            }

          else
            if(c == '[')
            {
              r.advance();
            }

          else
            if(c == '{')
            {
              r.advance();
            }

          else
            if((c == ')') ||
               (c == ']') ||
               (c == '}'))
            {
              printf("開いてない\'%c\'が出現\n",c);

              break;
            }
        }
    }
}


const stmt*  block::begin() const noexcept{return m_stmt_list.data();}
const stmt*    block::end() const noexcept{return m_stmt_list.data()+m_stmt_list.size();}


}}




