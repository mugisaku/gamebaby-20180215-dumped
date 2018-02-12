#ifndef LIBGBSND_EXECUTION_CONTEXT_HPP
#define LIBGBSND_EXECUTION_CONTEXT_HPP


#include"libgbstd/string.hpp"
#include"libgbsnd/script.hpp"
#include"libgbsnd/expr.hpp"
#include<list>
#include<cstdint>
#include<vector>


namespace gbsnd{


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

  size_t  m_number_of_frames=0;

  struct frame;

  frame*  m_top_frame=nullptr;

  value  m_returned_value;

  uint32_t  m_rising_time;

  enum class state{
    not_ready,
    ready,
    sleeping,
    exited,

  } m_state=state::not_ready;


  void  return_(value  v) noexcept;

public:
  execution_context() noexcept{}
  execution_context(const script&  scr) noexcept{reset(scr);}
 ~execution_context(){clear();}

  void  clear() noexcept;

  void  reset(const script&  scr) noexcept;

  void  call(gbstd::string_view  routine_name, const std::vector<value>&  argument_list) noexcept;
  void  call(gbstd::string_view  routine_name, const routine&  routine, const expr_list&  argument_list) noexcept;

  size_t  get_number_of_frames() const noexcept{return m_number_of_frames;}

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




#endif




