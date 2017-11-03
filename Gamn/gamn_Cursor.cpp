#include"gmbb_Script__Cursor.hpp"




namespace gmbb{
namespace script{


void
Cursor::
advance(GoUpIfReachedEnd  g) noexcept
{
    if(current)
    {
      current = current->next;

        if(!current && g.value)
        {
          go_up();
        }
    }
}


bool
Cursor::
go_in(ListNode const*  nd) noexcept
{
    if(nd && (depth < stack_size))
    {
        if(current)
        {
          stack[depth++] = current;
        }


      current = nd;

      return true;
    }


  return false;
}


bool
Cursor::
go_up() noexcept
{
    if(depth)
    {
      current = stack[--depth];

      return true;
    }


  return false;
}


}}




