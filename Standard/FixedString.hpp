#ifndef FixedString_TEMPLATE
#define FixedString_TEMPLATE


#include"Pointer.hpp"


class
FixedString
{
  static constexpr size_t  get_length(Pointer<const char>  p, size_t  l) noexcept
  {
    return *p? get_length(p+1,l+1):l;
  }


public:
  const Pointer<const char>  pointer;

  const size_t  length;

  constexpr FixedString(const Pointer<const char>  p) noexcept:
  pointer(p),
  length(get_length(p,0)){}


  constexpr const char&  operator[](size_t  i) const noexcept{return pointer[i];}

  constexpr const Pointer<const char>  begin() const noexcept{return pointer       ;}
  constexpr const Pointer<const char>    end() const noexcept{return pointer+length;}

};


#endif




