#include"Director.hpp"
#include"Actor.hpp"
#include"Board.hpp"
#include<cstdio>




namespace gmbb{




void
Director::
update() noexcept
{
    if(script_processor)
    {
      script_processor(*this,script_current);
    }


  auto   it = context_table.begin();
  auto  end = context_table.end();

    while(it != end)
    {
      auto&  ctx = *it;

        if(ctx.current)
        {
          ++it;

          script_processor(*this,ctx.current);
        }

      else
        {
          it = context_table.erase(it);
        }
    }


  GroupTask::update();
}


void
Director::
print() const noexcept
{
  auto  next = get_const_first();

    while(next)
    {
//      next->print();

      printf(",");

      next = static_cast<Actor const*>(next->get_const_next());
    }
}


}




