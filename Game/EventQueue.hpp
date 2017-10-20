#ifndef GMBB_EventQueue_HPP
#define GMBB_EventQueue_HPP


#include"Event.hpp"


namespace gmbb{
namespace event_queue{


void  push(Event  evt) noexcept;

template<typename  T>
void
push(T  t)
{
  push(Event(t));
}


Event  pop() noexcept;

int  get_number_of_events() noexcept;


}}




#endif




