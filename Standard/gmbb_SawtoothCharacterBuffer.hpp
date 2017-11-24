#ifndef GMBB_SawtoothCharacterBUFFER_HPP_INCLUDED
#define GMBB_SawtoothCharacterBUFFER_HPP_INCLUDED


#include<cstdint>
#include<cstdio>
#include<string>
#include"Pointer.hpp"




namespace gmbb{


class
SawtoothCharacterBuffer
{
public:
  struct Line{
    rw_ptr<char16_t>  data;

    rw_ptr<Line>  next;
  };


  class Iterator{
    ro_ptr<Line>  ptr;

  public:
    Iterator(ro_ptr<Line>  p=nullptr) noexcept: ptr(p){}

    ro_ptr<char16_t>  operator*() const noexcept{return ptr->data.get_ro();}

    bool  operator!=(const Iterator&  rhs) const noexcept
    {
      return ptr != rhs.ptr;
    }


    Iterator&  operator++() noexcept
    {
      ptr = ptr->next.get_ro();

      return *this;
    }

  };

private:
  int  number_of_columns=0;
  int  number_of_rows=0;

  int  current_length=0;

  char16_t  last_char=0;

  char16_t*  data_source=nullptr;
  Line*      line_source=nullptr;

  rw_ptr<Line>    first;
  rw_ptr<Line>  current;
  rw_ptr<Line>     last;

public:
  SawtoothCharacterBuffer(                      ) noexcept{}
  SawtoothCharacterBuffer(int  col_n, int  row_n) noexcept{resize(col_n,row_n);}
 ~SawtoothCharacterBuffer(){clear();}

  int  get_number_of_columns() const noexcept{return number_of_columns;}
  int  get_number_of_rows() const noexcept{return number_of_rows;}

  void  clear() noexcept;

  void  reset() noexcept;

  void  resize(int  col_n, int  row_n) noexcept;

  void  rotate() noexcept;

  void  push(char16_t  c) noexcept;

  bool  is_full() const noexcept;

  Iterator  begin() const noexcept{return Iterator(first.get_ro());}
  Iterator    end() const noexcept{return Iterator(              );}

};


}




#endif




