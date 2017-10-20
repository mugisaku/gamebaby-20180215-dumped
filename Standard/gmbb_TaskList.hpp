#ifndef GMBB_TaskList_HPP
#define GMBB_TaskList_HPP


#include"gmbb_Task.hpp"


namespace gmbb{
namespace task_list{


void   push(Task&  t) noexcept;
void  erase(Task&  t) noexcept;

void  update() noexcept;

void  render(Image&  dst, Point  offset) noexcept;

void  print() noexcept;

}}




#endif




