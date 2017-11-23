#include"gmbb_SawtoothCharacterBuffer.hpp"




namespace gmbb{


namespace{
size_t
get_buffer_length(int  col_n, int  row_n) noexcept
{
  return (col_n+1)*row_n;
}
}


void
SawtoothCharacterBuffer::
clear() noexcept
{
  delete[] data_source          ;
           data_source = nullptr;
  delete[] line_source;
           line_source = nullptr;
}


void
SawtoothCharacterBuffer::
reset() noexcept
{
  current_length = 0;

  auto  cur = first;

    while(cur)
    {
      cur->data[0] = 0;

      cur = cur->next;
    }
}


void
SawtoothCharacterBuffer::
resize(int  col_n, int  row_n) noexcept
{
  clear();

  number_of_columns = col_n;
  number_of_rows    = row_n;

  current_length = 0;

  data_source = new char16_t[get_buffer_length(col_n,row_n)];
  line_source = new     Line[                         row_n];

  rw_ptr<char16_t>  data_p = data_source;
  rw_ptr<Line>      line_p = line_source;

    if(row_n > 0)
    {
      row_n -= 1;

                first = line_p++;
      current = first           ;

      current->data[0] = 0;

        while(row_n--)
        {
                    current->next = line_p++;
          current = current->next           ;

          current->data[0] = 0;
        }


      last = current        ;
             current = first;

      last->next = nullptr;
    }
}


void
SawtoothCharacterBuffer::
rotate() noexcept
{
  auto  old_first = first;

  first = old_first->next;

  last->next = old_first;

  last = old_first;

  last->next = nullptr;

  last->data[0] = 0;


  current = last;

  current_length = 0;
}


void
SawtoothCharacterBuffer::
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
          current->data[current_length++] = c;

            if(current_length > (number_of_columns-1))
            {
              current = current->next;
            }
        }
    }
}



bool
SawtoothCharacterBuffer::
is_full() const noexcept
{
  return !current;
}



}




