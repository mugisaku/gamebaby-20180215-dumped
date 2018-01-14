#ifndef LIBGBSND_EXECUTION_CONTEXT_HPP
#define LIBGBSND_EXECUTION_CONTEXT_HPP


#include"libgbstd/string.hpp"
#include<list>
#include<cstdint>


namespace gbsnd{
namespace devices{


class stmt;
class object;
class value;


class
execution_frame
{
  gbstd::string  m_routine_name;

  std::list<object>  m_object_list;

  uint32_t  m_pc=0;

  const stmt*  m_stmt_list=nullptr;

  size_t  m_number_of_stmts=0;

public:
  const object*  find_object(gbstd::string_view  name) const noexcept;

  operator bool() const noexcept{return 0;}

  const stmt*  get_stmt() noexcept;

};


class
execution_context
{
  size_t  m_max_number_of_frames=0;
  size_t      m_number_of_frames=0;

  execution_frame*  m_frame_stack  =nullptr;
  execution_frame*  m_frame_pointer=nullptr;

public:
  execution_context() noexcept{}
 ~execution_context(){clear();}

  void  clear() noexcept;

  void  resize(size_t  n) noexcept;

  const value*  seek_value(gbstd::string_view  name) const noexcept;

  void  step() noexcept;

};


}


using devices::execution_frame;
using devices::execution_context;


}




#endif




