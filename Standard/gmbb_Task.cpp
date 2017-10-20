#include"gmbb_Task.hpp"
#include"gmbb_TaskList.hpp"




namespace gmbb{




void
Task::
connect(Task&  new_next) noexcept
{
  new_next.previous = this;

  next = &new_next;
}


void
Task::
disconnect() noexcept
{
    if(previous)
    {
      previous->next = next;
    }


    if(next)
    {
      next->previous = previous;
    }


  previous = nullptr;
      next = nullptr;
}


}




