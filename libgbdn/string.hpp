#ifndef LIBGBDN_string_HPP
#define LIBGBDN_string_HPP


#include<cstddef>
#include<utility>


namespace gbdn{


class value;


class
string_view
{
  static constexpr size_t  get_length(const char*  p, size_t  l) noexcept
  {
    return *p? get_length(p+1,l+1):l;
  }


  static constexpr bool  compare(const char*  a, const char*  b, size_t  l) noexcept
  {
    return (*a == *b)? (l? compare(a+1,b+1,l-1):true)
          :false;
  }


  const char*  pointer;

  size_t  length;

public:
  constexpr string_view(const char*  p=nullptr) noexcept:
  pointer(p),
  length(p? get_length(p,0):0){}

  constexpr string_view(const char*  p, size_t  l) noexcept:
  pointer(p),
  length(l){}


  constexpr operator bool() const noexcept{return pointer;}

  constexpr bool  operator==(const char*  s) const noexcept{return compare(pointer,s,length);}

  constexpr bool  operator==(const string_view&  rhs) const noexcept
  {
    return(length == rhs.length) && compare(pointer,rhs.pointer,length);
  }

  constexpr const char&  operator[](int  i) const noexcept{return pointer[i];}

  constexpr const char*  get_data() const noexcept{return pointer;}

  constexpr size_t  get_length() const noexcept{return length;}

  constexpr const char*  begin() const noexcept{return pointer       ;}
  constexpr const char*    end() const noexcept{return pointer+length;}

};


class
string
{
  static char  null;

  char*  data=&null;

  size_t  length=0;

  value*  companion_value=nullptr;

public:
  string() noexcept{}
  string(const char*  str, size_t  len, value*  v=nullptr) noexcept{assign(str,len,v);}
  string(const string&   rhs) noexcept{*this = rhs;}
  string(      string&&  rhs) noexcept{*this = std::move(rhs);}
 ~string(){clear();}

  string&  operator=(const string&   rhs) noexcept;
  string&  operator=(      string&&  rhs) noexcept;

  bool  operator==(const char*  s) const noexcept{return get_view() == s;}
  bool  operator==(const string&  rhs) const noexcept{return get_view() == rhs.get_view();}
  bool  operator==(const string_view&  sv) const noexcept{return get_view() == sv;}

  void  clear() noexcept;

  void  assign(const char*  str, size_t  len, value*  v=nullptr) noexcept;

  const char*  get_data() const noexcept{return data;}
  size_t  get_length() const noexcept{return length;}

  string_view  get_view() const noexcept{return string_view(data,length);}

  const char*  begin() const noexcept{return data       ;}
  const char*    end() const noexcept{return data+length;}

  void          set_value(value*  v) noexcept;
  const value*  get_value() const noexcept{return companion_value;}

  void  print(int  indent=0) const noexcept;

};


}




#endif




