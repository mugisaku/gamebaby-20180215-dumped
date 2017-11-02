#ifndef GMBB_EventQueue_HPP
#define GMBB_EventQueue_HPP


#include"Event.hpp"


namespace gmbb{
namespace event_queue{


void  push(Event const&  evt) noexcept;
void  pull(Event&        evt) noexcept;

int  get_number_of_events() noexcept;


}}




#endif




