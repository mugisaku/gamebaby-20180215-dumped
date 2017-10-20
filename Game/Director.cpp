#include"Director.hpp"
#include"Actor.hpp"
#include"Board.hpp"
#include<cstdio>




namespace gmbb{




void
Director::
insert_to_first(Actor&  target) noexcept
{
    if(!target.test_active_flag())
    {
        if(first)
        {
          target.connect(*first);

          first = &target;
        }

      else
        {
          first = &target;
           last = &target;
        }


      target.set_active_flag();

      ++number_of_actors;
    }
}


void
Director::
insert_to_last(Actor&  target) noexcept
{
    if(!target.test_active_flag())
    {
        if(last)
        {
          last->connect(target);

          last = &target;
        }

      else
        {
          first = &target;
           last = &target;
        }


      target.set_active_flag();

      ++number_of_actors;
    }
}


void
Director::
remove(Actor&  target) noexcept
{
    if(target.test_active_flag())
    {
        if(this->first == &target)
        {
          this->first = target.get_next();
        }


        if(this->last == &target)
        {
          this->last = target.get_previous();
        }


      target.disconnect();

      target.unset_active_flag();

      --number_of_actors;
    }
}


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


  auto  next = first;

    while(next)
    {
      next->update();

      next = next->get_next();
    }
}


void
Director::
render(Image&  dst, Point  offset) const noexcept
{
  auto  next = first.get_const_raw_pointer();

  offset += board->get_view_point();

    while(next)
    {
      next->render(dst,offset);

      next = static_cast<Actor const*>(next->get_const_next());
    }
}


covered_ptr<Actor>
Director::
find_by_name(std::string const&  name_) const noexcept
{
  auto  next = first;

    while(next)
    {
        if(next->get_name() == name_)
        {
          return next;
        }


      next = next->get_next();
    }


  return nullptr;
}


void
Director::
print() const noexcept
{
  auto  next = first.get_const_raw_pointer();

    while(next)
    {
      next->print();

      printf(",");

      next = static_cast<Actor const*>(next->get_const_next());
    }
}


}




