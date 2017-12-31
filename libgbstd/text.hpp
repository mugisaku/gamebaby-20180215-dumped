#ifndef GMBB_text_HPP
#define GMBB_text_HPP


#include<string>
#include<cstdarg>
#include"libgbstd/ro_ptr.hpp"
#include"libgbstd/rw_ptr.hpp"
#include"libgbstd/unicode.hpp"
#include<initializer_list>


namespace gbstd{
namespace texts{


std::string_view  make_text(const char*  fmt, ...) noexcept;


class
text_buffer
{
  char*  m_data_source=nullptr;

  size_t  m_data_length=0;

  char*   m_input_pointer=nullptr;

  utf8_decoder  m_decoder;

public:
  text_buffer() noexcept{}
  text_buffer(size_t  length) noexcept{resize(length);}
 ~text_buffer(){clear();}

  void  clear() noexcept;
  void  reset() noexcept;

  void  resize(size_t  length) noexcept;

  bool  is_remaining() const noexcept{return(m_decoder.get_pointer() < m_input_pointer);}

  void  push(ro_ptr<char>  s, bool  with_newline=true);
  void  push(std::initializer_list<ro_ptr<char>>  ls);

  char16_t  pop() noexcept;

};


class
text_roll
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
  line*      m_line_source=nullptr;

  rw_ptr<line>    m_first;
  rw_ptr<line>  m_current;
  rw_ptr<line>     m_last;

public:
  text_roll(                      ) noexcept{}
  text_roll(int  col_n, int  row_n) noexcept{resize(col_n,row_n);}
 ~text_roll(){clear();}

  int  get_number_of_columns() const noexcept{return m_number_of_columns;}
  int  get_number_of_rows() const noexcept{return m_number_of_rows;}

  void  clear() noexcept;

  void  reset() noexcept;

  void  resize(int  col_n, int  row_n) noexcept;

  void  rotate() noexcept;

  void  push(char16_t  c) noexcept;

  bool  is_full() const noexcept;

  iterator  begin() const noexcept{return iterator(m_first.get_ro());}
  iterator    end() const noexcept{return iterator(                );}

};


}


using texts::make_text;


}




#endif




