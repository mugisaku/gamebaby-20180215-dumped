#include"Actor.hpp"
#include"Director.hpp"
#include<cstdlib>




namespace gmbb{




void
Actor::
update() noexcept
{
    if(action_stack.size())
    {
      auto  a = action_stack.back();

      (*a)();

        if(!--a->counter)
        {
          delete a;

          action_stack.pop_back();
        }
    }
}




}




