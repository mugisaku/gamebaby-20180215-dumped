#include"EventQueue.hpp"


namespace gmbb{
namespace event_queue{


namespace{


struct
Node
{
  Event  event;

  Node*  next=nullptr;

  Node(Event const&  evt): event(evt){}

};


Node*  first=nullptr;
Node*   last=nullptr;

int  number=0;


}




void
push(Event const&  evt) noexcept
{
  auto  nd = new Node(evt);

    if(last)
    {
      last->next = nd;
      last       = nd;
    }

  else
    {
      first = nd;
       last = nd;
    }


  ++number;
}


void
pull(Event&  evt) noexcept
{
  evt = first->event;

  auto  next = first->next;

  delete first       ;
         first = next;

  --number;

    if(!first)
    {
      last = nullptr;
    }
}


int
get_number_of_events() noexcept
{
  return number;
}




}}




