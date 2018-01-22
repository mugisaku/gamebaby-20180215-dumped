#include"libgbsnd/stmt.hpp"
#include"libgbsnd/script.hpp"


namespace gbsnd{
namespace devices{


block::
block(const script_token_string&  toks) noexcept
{
  script_token_cursor  cur(toks);

    while(cur)
    {
        if(cur[0].is_identifier())
        {
          using  sv = gbstd::string_view;

          sv  id(cur[0].get_identifier().view());

               if(id == sv("return")){}
          else if(id == sv("while")){}
          else if(id == sv("if")){}
          else if(id == sv("for")){}
          else if(id == sv("switch")){}
          else if(id == sv("case")){}
          else if(id == sv("goto")){}
          else if(id == sv("default")){}
          else if(id == sv("break")){}
          else if(id == sv("continue")){}
          else
            {
              auto  e = make_expr(cur);

              e->print();
printf("\n");
            }
cur += 1;
        }

      else
        if(cur[0].is_semicolon())
        {
          cur += 1;
        }

      else
        {
          printf("**error**\n");

          break;
        }
    }
}


const stmt*  block::begin() const noexcept{return m_stmt_list.data();}
const stmt*    block::end() const noexcept{return m_stmt_list.data()+m_stmt_list.size();}


}}




