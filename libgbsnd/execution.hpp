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
execution_context
{
  script  m_script;

  size_t  m_max_number_of_frames=0;
  size_t      m_number_of_frames=0;

  struct frame;

  frame*  m_frame_stack=nullptr;

  value  m_returned_value;

  void  step_evaluation(execution_context::frame&  frame) noexcept;

public:
  execution_context(const script&  scr) noexcept;
 ~execution_context(){clear();}

  void  clear() noexcept;

  bool  test_capacity() const noexcept{return m_number_of_frames < m_max_number_of_frames;}

  void  call(gbstd::string_view  routine_name, const std::vector<value>&  argument_list) noexcept;

  size_t  get_max_number_of_frames() const noexcept{return m_max_number_of_frames;}
  size_t      get_number_of_frames() const noexcept{return     m_number_of_frames;}

  void  resize(size_t  n) noexcept;

  value  get_value(gbstd::string_view  name) const noexcept;

  const value  get_returned_value() const noexcept{return m_returned_value;}


  enum class result{
    slept,
    returned,

  };


  result  run() noexcept;

};


}


using devices::execution_context;


}




#endif




