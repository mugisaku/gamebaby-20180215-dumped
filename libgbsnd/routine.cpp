#include"libgbsnd/routine.hpp"


namespace gbsnd{
namespace devices{




routine&
routine::
operator=(const routine&   rhs) noexcept
{
  clear();

  m_name = rhs.m_name;
  m_block = duplicate(rhs.m_block);

  return *this;
}


routine&
routine::
operator=(routine&&  rhs) noexcept
{
  clear();

  std::swap(m_name ,rhs.m_name );
  std::swap(m_block,rhs.m_block);

  return *this;
}




void
routine::
clear() noexcept
{
  m_name.clear();

  delete m_block          ;
         m_block = nullptr;
}



}}




