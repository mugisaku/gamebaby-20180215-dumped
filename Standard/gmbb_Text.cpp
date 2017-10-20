#include"gmbb_Text.hpp"




namespace gmbb{


struct
Text::
Line
{
  std::u16string  string;

  Line*  next=nullptr;

};


Text::
Text(int  col_n, int  row_n) noexcept:
column_number(col_n),
row_number(row_n)
{
    if(row_n > 0)
    {
      row_n -= 1;

      first = new Line;

      current = first;

        while(row_n--)
        {
          auto  line = new Line;

          current->next = line;

          current = line;
        }


      last = current        ;
             current = first;
    }
}




void
Text::
clear() noexcept
{
  auto  next = first;

   while(next)
   {
     next->string.clear();

     next = next->next;
   }


  current = first;
}


void
Text::
rotate() noexcept
{
  auto  old_first = first;

  first = old_first->next;

  last->next = old_first;

  last = old_first;

  last->next = nullptr;

  last->string.clear();


  current = last;
}


void
Text::
push(char16_t  c) noexcept
{
    if(!is_full())
    {
        if(c == '\n')
        {
          current = current->next;
        }

      else
        {
          current->string.push_back(c);

            if(current->string.size() > (column_number-1))
            {
              current = current->next;
            }
        }
    }
}



bool
Text::
is_full() const noexcept
{
  return !current;
}


void
Text::
render(Image&  dst, Point  point, GlyphSet const&  glset, ColorIndex const*  coloring) const noexcept
{
  auto  next = first;

    while(next)
    {
      dst.print(next->string.data(),point,glset,coloring);

      point.y += glset.get_height();

      next = next->next;
    }
}



}




