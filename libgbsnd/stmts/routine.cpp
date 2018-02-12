#include"libgbsnd/object.hpp"
#include"libgbsnd/script.hpp"
#include"libgbsnd/stmt.hpp"


namespace gbsnd{
namespace stmts{




routine::
routine(const script_token_string&  parals_src, const script_token_string&  blk_src) noexcept
{
  std::vector<gbstd::string>  buf;

    for(auto&  tok: parals_src)
    {
         if(!tok.is_identifier())
         {
           break;
         }


      buf.emplace_back(tok.get_identifier().view());
    }


  m_parameter_list = parameter_list(buf.data(),buf.size());

  m_stmt_list = stmt_list(blk_src);
}




void
routine::
print() const noexcept
{
  printf("(");

    for(auto&  s: m_parameter_list)
    {
      printf("%s,",s.data());
    }


  printf(")");

  printf("\n{\n");

    for(auto&  stmt: m_stmt_list)
    {
      stmt.print();

      printf("\n");
    }


  printf("}\n\n\n");
}


}}




