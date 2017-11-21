#ifndef Pointer_TEMPLATE
#define Pointer_TEMPLATE




template<typename  T>
class
Pointer
{
  T*  data;

public:
  using value_type = T;

  constexpr Pointer(T*  ptr=nullptr) noexcept:data(ptr){}

  constexpr value_type*  operator->() const noexcept{return  data;}
  constexpr value_type&  operator *() const noexcept{return *data;}

  constexpr bool  operator==(const T*  rhs) const noexcept{return data == rhs;}
  constexpr bool  operator!=(const T*  rhs) const noexcept{return data != rhs;}

  constexpr Pointer  operator+(int     i) const noexcept{return Pointer(data+i);}
  constexpr Pointer  operator+(size_t  i) const noexcept{return Pointer(data+i);}

  constexpr Pointer&  operator++() noexcept
  {
    ++data;

    return *this;
  }


  constexpr value_type&  operator[](size_t  i) const noexcept{return data[i];}

  constexpr operator bool() const noexcept{return data;}

  void  release() const noexcept{delete data;}

};


#endif




