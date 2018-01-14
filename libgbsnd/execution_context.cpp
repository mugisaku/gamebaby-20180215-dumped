#include"libgbsnd/execution.hpp"
#include"libgbsnd/object.hpp"


namespace gbsnd{
namespace devices{


void
execution_context::
clear() noexcept
{
  delete[] m_frame_stack          ;
           m_frame_stack = nullptr;

  m_frame_pointer = nullptr;

  m_max_number_of_frames = 0;
  m_number_of_frames     = 0;
}


void
execution_context::
resize(size_t  n) noexcept
{
  auto  new_ptr = new execution_frame[n];

    for(int  i = 0;  i < m_number_of_frames;  ++i)
    {
      new_ptr[i] = std::move(m_frame_stack[i]);
    }


  delete[] m_frame_stack          ;
           m_frame_stack = new_ptr;

  m_max_number_of_frames = n;

    if(m_number_of_frames)
    {
      m_frame_pointer = &m_frame_stack[m_number_of_frames-1];
    }
}


const value*
execution_context::
seek_value(gbstd::string_view  name) const noexcept
{
    if(m_frame_pointer)
    {
      auto  o = m_frame_pointer->find_object(name);
    }


  return nullptr;
}


void
execution_context::
step() noexcept
{
    if(m_frame_pointer)
    {
      auto  stmt = m_frame_pointer->get_stmt();
    }
}


}}




