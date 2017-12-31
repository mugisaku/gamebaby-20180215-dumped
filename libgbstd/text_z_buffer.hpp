#ifndef GMBB_text_z_buffer_HPP_INCLUDED
#define GMBB_text_z_buffer_HPP_INCLUDED


#include<cstdint>
#include<cstdio>
#include<string>
#include"rw_ptr.hpp"




namespace gbstd{
namespace texts{


class
z_buffer
{
public:
  struct line{
    rw_ptr<char16_t>  data;

    rw_ptr<line>  next;
  };


  class iterator{
    ro_ptr<line>  m_ptr;

  public:
    iterator(ro_ptr<line>  p=nullptr) noexcept: m_ptr(p){}

    ro_ptr<char16_t>  operator*() const noexcept{return m_ptr->data.get_ro();}

    bool  operator!=(const iterator&  rhs) const noexcept
    {
      return m_ptr != rhs.m_ptr;
    }


    iterator&  operator++() noexcept
    {
      m_ptr = m_ptr->next.get_ro();

      return *this;
    }

  };

private:
  int  m_number_of_columns=0;
  int  m_number_of_rows=0;

  int  m_current_length=0;

  char16_t  m_last_char=0;

  char16_t*  m_data_source=nullptr;
  Line*      m_line_source=nullptr;

  rw_ptr<Line>    m_first;
  rw_ptr<Line>  m_current;
  rw_ptr<Line>     m_last;

public:
  z_buffer(                      ) noexcept{}
  z_buffer(int  col_n, int  row_n) noexcept{resize(col_n,row_n);}
 ~z_buffer(){clear();}

  int  get_number_of_columns() const noexcept{return m_number_of_columns;}
  int  get_number_of_rows() const noexcept{return m_number_of_rows;}

  void  clear() noexcept;

  void  reset() noexcept;

  void  resize(int  col_n, int  row_n) noexcept;

  void  rotate() noexcept;

  void  push(char16_t  c) noexcept;

  bool  is_full() const noexcept;

  Iterator  begin() const noexcept{return iterator(m_first.get_ro());}
  Iterator    end() const noexcept{return iterator(              );}

};


}


using texts::z_buffer;


}


#endif




