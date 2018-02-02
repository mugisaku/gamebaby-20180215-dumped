#include"libgbsnd/routine.hpp"
#include"libgbsnd/script.hpp"
#include"libgbsnd/stmt.hpp"


namespace gbsnd{
namespace devices{




routine::
routine(const script_token_string&  parals_src, const script_token_string&  blk_src) noexcept
{
    for(auto&  tok: parals_src)
    {
         if(!tok.is_identifier())
         {
           break;
         }


      m_parameter_list.emplace_back(tok.get_identifier().view());
    }


//  m_block = new block(blk_src);
}




routine&
routine::
operator=(const routine&   rhs) noexcept
{
    if(this != &rhs)
    {
      m_parameter_list = rhs.m_parameter_list;
      m_stmt_list.reset(gbstd::duplicate(rhs.m_stmt_list.get()));
    }


  return *this;
}


routine&
routine::
operator=(routine&&  rhs) noexcept
{
    if(this != &rhs)
    {
      std::swap(m_parameter_list,rhs.m_parameter_list);
      std::swap(m_stmt_list     ,rhs.m_stmt_list     );
    }


  return *this;
}




void
routine::
set_parameter_list(parameter_list&&  ls) noexcept
{
  m_parameter_list = std::move(ls);
}


const parameter_list&
routine::
get_parameter_list() const noexcept
{
  return m_parameter_list;
}


void
routine::
set_stmt_list(stmt_list*  ls) noexcept
{
  m_stmt_list.reset(ls);
}


const std::unique_ptr<stmt_list>&
routine::
get_stmt_list() const noexcept
{
  return m_stmt_list;
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

    if(m_stmt_list)
    {
      printf("\n");

        for(auto&  stmt: *m_stmt_list)
        {
          stmt.print();
        }
    }
}


}}




