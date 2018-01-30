#ifndef LIBGBSND_EXECUTION_CONTEXT_HPP
#define LIBGBSND_EXECUTION_CONTEXT_HPP


#include"libgbstd/string.hpp"
#include"libgbsnd/script.hpp"
#include<list>
#include<cstdint>
#include<vector>


namespace gbsnd{
namespace devices{


class stmt;
class object;
class value;
class routine;


struct
millisecond
{
  uint32_t  value;
};


class
execution_context
{
  script  m_script;

  size_t  m_max_number_of_frames=0;
  size_t      m_number_of_frames=0;

  struct frame;

  frame*  m_frame_stack=nullptr;

  value  m_returned_value;

  uint32_t  m_rising_time;

  enum class state{
    not_ready,
    ready,
    sleeping,
    exited,

  } m_state=state::not_ready;


  void  step_evaluation(execution_context::frame&  frame) noexcept;

  void  return_(value  v) noexcept;

public:
  execution_context() noexcept{}
  execution_context(const script&  scr) noexcept{reset(scr);}
 ~execution_context(){clear();}

  void  clear() noexcept;

  void  reset(const script&  scr) noexcept;

  bool  test_capacity() const noexcept{return m_number_of_frames < m_max_number_of_frames;}

  void  call(gbstd::string_view  routine_name, const std::vector<value>&  argument_list) noexcept;

  size_t  get_max_number_of_frames() const noexcept{return m_max_number_of_frames;}
  size_t      get_number_of_frames() const noexcept{return     m_number_of_frames;}

  void  resize(size_t  n) noexcept;

  value  get_value(gbstd::string_view  name) const noexcept;

  const value  get_returned_value() const noexcept{return m_returned_value;}

  bool  is_not_ready() const noexcept{return m_state == state::not_ready;}
  bool  is_ready()     const noexcept{return m_state == state::ready;}
  bool  is_sleeping()  const noexcept{return m_state == state::sleeping;}
  bool  is_exited()    const noexcept{return m_state == state::exited;}

  void  run(millisecond  ms) noexcept;

};


}


using devices::execution_context;
using devices::millisecond;


}




#endif




