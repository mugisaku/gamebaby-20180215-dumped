#include"gmbb_TaskList.hpp"


namespace gmbb{
namespace task_list{


namespace{


covered_ptr<Task>  first;
covered_ptr<Task>   last;


}




void
push(Task&  t) noexcept
{
    if(!t.test_active_flag())
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


      t.set_active_flag();
    }
}


void
erase(Task&  t) noexcept
{
    if(t.test_active_flag())
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

      t.unset_active_flag();
    }
}


void
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
render(Image&  dst, Point  offset) noexcept
{
  auto  current = first.get_const_raw_pointer();

    while(current)
    {
      current->render(dst,offset);

      current = current->get_const_next();
    }
}


void
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




}}




