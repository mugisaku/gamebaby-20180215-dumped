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
  int     for_count;
  int   while_count;
  int  switch_count;

};


void
build(const char*  label_base,
      const char*     break_label,
      const char*  continue_label, context&  ctx, script_token_cursor&  cur, stmt_list&  ls) noexcept
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
                  gbstd::tmpstr  co_label_base("WHILE%03d",ctx.while_count++);
                  gbstd::tmpstr    begin_label("%s_BEGIN" ,*co_label_base);
                  gbstd::tmpstr      end_label("%s_END"   ,*co_label_base);


                  ls.emplace_back(label_stmt(*begin_label));


                  script_token_cursor  expr_cur(cur[0].get_token_string());

                  ls.emplace_back(branch_stmt(expr_array(expr_cur),*end_label,false));


                  script_token_cursor  blk_cur(cur[1].get_token_string());

                  build(*co_label_base,*end_label,*begin_label,ctx,blk_cur,ls);


                  ls.emplace_back(label_stmt(*end_label));


                  cur += 2;
                }

              else
                {
                  printf("while構文が不正\n");

                  break;
                }
            }

          else
            if(id == sv("if"))
            {
              cur += 1;

              int  block_number = 0;

                if(cur[0].is_token_string('(',')') &&
                   cur[1].is_token_string('{','}'))
                {
                  gbstd::tmpstr  co_label_base("IF%03d",ctx.if_count++);
                  gbstd::tmpstr      end_label("%s_END",*co_label_base);
                  gbstd::tmpstr     next_label("%s_%03d",*co_label_base,++block_number);


                  script_token_cursor  expr_cur(cur[0].get_token_string());

                  ls.emplace_back(branch_stmt(expr_array(expr_cur),*next_label,false));


                  script_token_cursor  blk_cur(cur[1].get_token_string());

                  build(*co_label_base,break_label,continue_label,ctx,blk_cur,ls);


                  ls.emplace_back(jump_stmt(*end_label));


                  cur += 2;

                    while(cur[0].is_identifier({gbstd::string_view("else")}))
                    {
                      cur += 1;

                      ls.emplace_back(label_stmt(*next_label));

                        if(cur[0].is_token_string('{','}'))
                        {
                          blk_cur = script_token_cursor(cur[0].get_token_string());

                          build(*co_label_base,break_label,continue_label,ctx,blk_cur,ls);

                          cur += 1;

                          break;
                        }

                      else
                        if(cur[0].is_identifier({gbstd::string_view("if")}) &&
                           cur[1].is_token_string('(',')') &&
                           cur[2].is_token_string('{','}'))
                        {
                          next_label("%s_%03d",*co_label_base,++block_number);


                          expr_cur = script_token_cursor(cur[1].get_token_string());

                          ls.emplace_back(branch_stmt(expr_array(expr_cur),*next_label,false));


                          blk_cur = script_token_cursor(cur[2].get_token_string());

                          ls.emplace_back(jump_stmt(*end_label));

                          cur += 3;
                        }
                    }


                  ls.emplace_back(label_stmt(*end_label));
                }

              else
                {
                  printf("if構文が不正\n");

                  break;
                }
            }

          else
            if(id == sv("for"))
            {
            }

          else
            if(id == sv("switch"))
            {
              cur += 1;

                if(cur[0].is_token_string('(',')') &&
                   cur[1].is_token_string('{','}'))
                {
                  gbstd::tmpstr  co_label_base("SWITCH%03d",ctx.switch_count++);
                  gbstd::tmpstr    begin_label("%s_BEGIN" ,*co_label_base);
                  gbstd::tmpstr      end_label("%s_END"   ,*co_label_base);


                  ls.emplace_back(label_stmt(*begin_label));


                  script_token_cursor  expr_cur(cur[0].get_token_string());

                  ls.emplace_back(branch_stmt(expr_array(expr_cur),*end_label,false));


                  script_token_cursor  blk_cur(cur[1].get_token_string());

                  build(*co_label_base,*end_label,*begin_label,ctx,blk_cur,ls);


                  ls.emplace_back(label_stmt(*end_label));


                  cur += 2;
                }

              else
                {
                  printf("switch構文が不正\n");

                  break;
                }
            }

          else
            if(id == sv("case"))
            {
            }

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

              ls.emplace_back(jump_stmt(break_label));
            }

          else
            if(id == sv("continue"))
            {
              ++cur;

              ls.emplace_back(jump_stmt(continue_label));
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

  build("","","",ctx,cur,*ls);

  return ls;
}




}}




