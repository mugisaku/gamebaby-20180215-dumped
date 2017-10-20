#include"gmbb_GroupTask.hpp"


namespace gmbb{




void
GroupTask::
push_to_first(Task&  t) noexcept
{
    if(!t.get_group())
    {
        if(first)
        {
          t.connect(*first);
          first = &t;
        }

      else
        {
          first = &t;
           last = &t;
        }


      t.set_group(*this);

      ++number;
    }
}


void
GroupTask::
push_to_last(Task&  t) noexcept
{
    if(!t.get_group())
    {
        if(last)
        {
          last->connect(t);
          last = &t;
        }

      else
        {
          first = &t;
           last = &t;
        }


      t.set_group(*this);

      ++number;
    }
}


void
GroupTask::
erase(Task&  t) noexcept
{
    if(t.get_group())
    {
        if(first == &t)
        {
          first = first->get_next();
        }


        if(last == &t)
        {
          last = last->get_previous();
        }


      t.disconnect();

      --number;
    }
}


covered_ptr<Task>
GroupTask::
find_by_name(std::string const&  name_) const noexcept
{
  auto  next = first;

    while(next)
    {
        if(next->get_name() == name_)
        {
          return next;
        }

      else
        if(next->is_group())
        {
          auto  cogrp = static_cast<GroupTask const*>(next.get_const_raw_pointer());

          auto  res = cogrp->find_by_name(name_);

            if(res)
            {
              return res;
            }
        }


      next = next->get_next();
    }


  return nullptr;
}


void
GroupTask::
update() noexcept
{
  auto  current = first;

    while(current)
    {
      current->update();

      current = current->get_next();
    }
}


void
GroupTask::
render(Image&  dst, Point  offset) const noexcept
{
  auto  current = first.get_const_raw_pointer();

  offset += get_base_point();

    while(current)
    {
      current->render(dst,offset);

      current = current->get_const_next();
    }
}


void
GroupTask::
print() noexcept
{
  auto  current = first.get_const_raw_pointer();

  printf("[print task]\n");

    while(current)
    {
      printf("%s\n",current->get_name().data());

      current = current->get_const_next();
    }


  printf("end\n\n");
}




}




