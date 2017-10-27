#ifndef GMBB_Script__Cursor_HPP
#define GMBB_Script__Cursor_HPP


#include"covered_ptr"
#include"gmbb_Script__List.hpp"


namespace gmbb{
namespace script{


class
Cursor
{
  static constexpr size_t  stack_size = 32;

  ListNode const*  stack[stack_size];

  int  depth=0;

  ListNode const*  current;

public:
  struct GoUpIfReachedEnd{
    bool  value;

    constexpr GoUpIfReachedEnd(bool  v=true) noexcept: value(v){}
  };


  Cursor(ListNode const*  start=nullptr) noexcept: current(start){}

  Value const&  operator*()  const noexcept{return current->value;}
  Value const*  operator->()  const noexcept{return &current->value;}

  operator bool()  const noexcept{return current;}

  void  advance(GoUpIfReachedEnd  g=true) noexcept;

  bool  go_in(ListNode const*  nd) noexcept;
  bool  go_up() noexcept;

};


}}




#endif




