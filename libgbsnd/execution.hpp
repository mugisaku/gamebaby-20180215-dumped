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


class
execution_frame
{
  gbstd::string  m_routine_name;

  std::list<object>  m_object_list;

  uint32_t  m_pc=0;

  const stmt*  m_stmt_list=nullptr;

  size_t  m_number_of_stmts=0;

public:
  execution_frame() noexcept{}

  void  assign(gbstd::string_view  name, const routine&  r, const std::vector<value>&  args) noexcept;

  const gbstd::string&  get_routine_name() const noexcept{return m_routine_name;}

  const object*  find_object(gbstd::string_view  name) const noexcept;

  operator bool() const noexcept{return 0;}

  const stmt*  get_stmt() noexcept;

};


class
execution_context
{
  script  m_script;

  size_t  m_max_number_of_frames=0;
  size_t      m_number_of_frames=0;

  execution_frame*  m_frame_stack=nullptr;

public:
  execution_context(const script&  scr) noexcept;
 ~execution_context(){clear();}

  void  clear() noexcept;

  bool  test_capacity() const noexcept{return m_number_of_frames < m_max_number_of_frames;}

  execution_frame&  get_top_frame() noexcept{return m_frame_stack[m_number_of_frames-1];}

  void  call(gbstd::string_view  routine_name, const std::vector<value>&  argument_list) noexcept;

  size_t  get_max_number_of_frames() const noexcept{return m_max_number_of_frames;}
  size_t      get_number_of_frames() const noexcept{return     m_number_of_frames;}

  void  resize(size_t  n) noexcept;

  const value*  seek_value(gbstd::string_view  name) const noexcept;

  void  step() noexcept;

};


}


using devices::execution_frame;
using devices::execution_context;


}




#endif




