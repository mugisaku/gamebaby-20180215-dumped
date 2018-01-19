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


  m_block = new block(blk_src);
}




routine&
routine::
operator=(const routine&   rhs) noexcept
{
  clear();

  m_parameter_list = rhs.m_parameter_list;
  m_block          = gbstd::duplicate(rhs.m_block);

  return *this;
}


routine&
routine::
operator=(routine&&  rhs) noexcept
{
  clear();

  std::swap(m_parameter_list,rhs.m_parameter_list);
  std::swap(m_block         ,rhs.m_block         );

  return *this;
}




void
routine::
clear() noexcept
{
  m_parameter_list.clear();

  delete m_block          ;
         m_block = nullptr;
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
set_block(block*  blk) noexcept
{
  delete m_block      ;
         m_block = blk;
}


const block*
routine::
get_block() const noexcept
{
  return m_block;
}


}}




