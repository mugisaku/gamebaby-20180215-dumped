#ifndef GMBB_text_i_buffer_HPP_INCLUDED
#define GMBB_text_i_buffer_HPP_INCLUDED


#include"rw_ptr.hpp"
#include<initializer_list>




namespace gbstd{
namespace texts{


class
i_buffer
{
  char*  m_data_source=nullptr;

  size_t  m_data_length=0;

  rw_ptr<char>   m_input_pointer;

  utf8_decoder  m_decoder;

public:
  i_buffer() noexcept{}
  i_buffer(size_t  length) noexcept{resize(length);}
 ~i_buffer(){clear();}

  void  clear() noexcept;
  void  reset() noexcept;

  void  resize(size_t  length) noexcept;

  bool  is_remaining() const noexcept{return(m_decoder.get_pointer() < m_input_pointer);}

  void  push(ro_ptr<char>  s, bool  with_newline=true);
  void  push(std::initializer_list<ro_ptr<char>>  ls);

  char16_t  pop() noexcept;

};


}




#endif




