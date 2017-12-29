#ifndef GMBB_LinearCharacterBuffer_HPP_INCLUDED
#define GMBB_LinearCharacterBuffer_HPP_INCLUDED


#include"Pointer.hpp"
#include<initializer_list>




namespace gmbb{


class
LinearCharacterBuffer
{
  char*  data_source=nullptr;

  size_t  data_length=0;

  ro_ptr<char>  data_tail;

  rw_ptr<char>   input_pointer;
  ro_ptr<char>  output_pointer;

public:
  LinearCharacterBuffer() noexcept{}
  LinearCharacterBuffer(size_t  length) noexcept{resize(length);}
 ~LinearCharacterBuffer(){clear();}

  void  clear() noexcept;
  void  reset() noexcept;

  void  resize(size_t  length) noexcept;

  bool  is_remaining() const noexcept{return(output_pointer < input_pointer);}

  void  push(ro_ptr<char>  s, bool  with_newline=true);
  void  push(std::initializer_list<ro_ptr<char>>  ls);

  char16_t  pop() noexcept;

};


}




#endif




