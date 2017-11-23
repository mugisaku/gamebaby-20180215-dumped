#ifndef FixedString_TEMPLATE
#define FixedString_TEMPLATE


#include"Pointer.hpp"


class
FixedString
{
  static constexpr size_t  get_length(ro_ptr<char>  p, size_t  l) noexcept
  {
    return *p? get_length(p+1,l+1):l;
  }


public:
  const ro_ptr<char>  pointer;

  const size_t  length;

  constexpr FixedString(ro_ptr<char>  p) noexcept:
  pointer(p),
  length(get_length(p,0)){}


  constexpr const char&  operator[](int  i) const noexcept{return pointer[i];}

  constexpr ro_ptr<char>  begin() const noexcept{return pointer                         ;}
  constexpr ro_ptr<char>    end() const noexcept{return pointer+static_cast<int>(length);}

};


#endif




