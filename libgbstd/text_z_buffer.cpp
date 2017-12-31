#include"text_z_buffer.hpp"




namespace gbstd{
namespace texts{


namespace{
size_t
get_buffer_length(int  col_n, int  row_n) noexcept
{
  return (col_n+1)*row_n;
}
}


void
z_buffer::
clear() noexcept
{
  delete[] m_data_source          ;
           m_data_source = nullptr;
  delete[] m_line_source;
           m_line_source = nullptr;
}


void
z_buffer::
reset() noexcept
{
  m_current_length = 0;

  auto  cur = m_first;

    while(cur)
    {
      cur->data[0] = 0;

      cur = cur->next;
    }


  m_current = m_first;

  m_last->next = nullptr;
}


void
z_buffer::
resize(int  col_n, int  row_n) noexcept
{
    if(row_n <= 1)
    {
      printf("[resize error]\n");

      return;
    }


  clear();

  m_number_of_columns = col_n;
  m_number_of_rows    = row_n;

  m_current_length = 0;

  m_data_source = new char16_t[get_buffer_length(col_n,row_n)];
  m_line_source = new     line[                         row_n];

  rw_ptr<char16_t>  data_p = m_data_source;
  rw_ptr<Line>      line_p = m_line_source;

    if(row_n > 0)
    {
      row_n -= 1;

                  m_first = line_p++;
      m_current = m_first           ;

      m_current->data = data_p           ;
                        data_p += col_n+1;

      m_current->data[0] = 0;

        while(row_n--)
        {
                      m_current->next = line_p++;
          m_current = m_current->next           ;

          m_current->data = data_p           ;
                            data_p += col_n+1;

          m_current->data[0] = 0;
        }


      m_last = m_current          ;
               m_current = m_first;

      m_last->next = nullptr;
    }
}


void
z_buffer::
rotate() noexcept
{
  auto  old_first = m_first;

  m_first = old_first->next;

  m_last->next = old_first;

  m_last = old_first;

  m_last->next = nullptr;

  m_last->data[0] = 0;


  m_current = m_last;

  m_current_length = 0;
}


void
z_buffer::
push(char16_t  c) noexcept
{
    if(!is_full())
    {
        if(c == '\n')
        {
          m_current = m_current->next;

          m_current_length = 0;
        }

      else
        if(c)
        {
          m_current->data[m_current_length++] = c;
          m_current->data[m_current_length  ] = 0;

            if(m_current_length > (m_number_of_columns-1))
            {
              m_current = m_current->next;

              m_current_length = 0;
            }
        }
    }
}



bool
z_buffer::
is_full() const noexcept
{
  return !m_current;
}



}}




