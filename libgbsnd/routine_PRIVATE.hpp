#ifndef LIBGBSND_ROUTINE_provate_HPP
#define LIBGBSND_ROUTINE_provate_HPP


#include"libgbsnd/routine.hpp"
#include"libgbsnd/stmt.hpp"


namespace gbsnd{
namespace devices{


struct
routine::
data
{
  size_t  m_reference_count=1;

  parameter_list  m_parameter_list;

  block*  m_block=nullptr;

  ~data()
  {
    delete m_block;
  }

};


}}




#endif




