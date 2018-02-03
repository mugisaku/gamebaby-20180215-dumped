#include"libgbsnd/stmt.hpp"
#include"libgbsnd/script.hpp"
#include"libgbstd/utility.hpp"


namespace gbsnd{
namespace devices{




namespace{


struct
context
{
  int      if_count;
  int   while_count;
  int  switch_count;

};


void
build(const char*  label_base, context&  ctx, script_token_cursor&  cur, stmt_list&  ls) noexcept
{
    while(cur)
    {
        if(cur[0].is_identifier())
        {
          using  sv = gbstd::string_view;

          sv  id(cur[0].get_identifier().view());

            if(id == sv("return"))
            {
              ++cur;

              ls.emplace_back(return_stmt(expr_array(cur)));
            }

          else
            if(id == sv("sleep"))
            {
              ++cur;

              ls.emplace_back(sleep_stmt(expr_array(cur)));
            }

          else
            if(id == sv("print"))
            {
              ++cur;

              ls.emplace_back(print_stmt(expr_array(cur)));
            }

          else
            if(id == sv("while"))
            {
              cur += 1;

                if(cur[0].is_token_string('(',')') &&
                   cur[1].is_token_string('{','}'))
                {
                  gbstd::tmpstr  while_label_base("WHILE%03d",ctx.while_count++);
                  gbstd::tmpstr  while_begin_label("%s_BEGIN",while_label_base);
                  gbstd::tmpstr    while_end_label  ("%s_END",while_label_base);


                  ls.emplace_back(label_stmt(*while_begin_label));


                  script_token_cursor  expr_cur(cur[0].get_token_string());

                  ls.emplace_back(branch_stmt(expr_array(expr_cur),*while_end_label,false));


                  script_token_cursor  blk_cur(cur[1].get_token_string());

                  build(*while_label_base,ctx,blk_cur,ls);


                  ls.emplace_back(label_stmt(*	while_end_label));


                  cur += 2;
                }

              else
                {
                  printf("while構文が不正\n");

                  break;
                }
            }

          else if(id == sv("if")){}
          else if(id == sv("for")){}
          else if(id == sv("switch")){}
          else if(id == sv("case")){}
          else
            if(id == sv("goto"))
            {
              ++cur;

                if(!cur[0].is_identifier())
                {
                  printf("gotoのための識別子がない\n");

                  break;
                }


              ls.emplace_back(jump_stmt(cur->get_identifier().view()));

              ++cur;
            }

          else
            if(id == sv("default"))
            {
              ++cur;
            }

          else
            if(id == sv("break"))
            {
              ++cur;

              gbstd::tmpstr  label("%s_END",label_base);

              ls.emplace_back(jump_stmt(*label));
            }

          else
            if(id == sv("continue"))
            {
              ++cur;

              gbstd::tmpstr  label("%s_BEGIN",label_base);

              ls.emplace_back(jump_stmt(*label));
            }

          else
            {
              ls.emplace_back(expr_array(cur));
            }
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
}


stmt_list*
build_stmt_list(const script_token_string&  toks) noexcept
{
  auto  ls = new stmt_list;

  script_token_cursor  cur(toks);

  context  ctx = {0};

  build("",ctx,cur,*ls);

  return ls;
}




}}




