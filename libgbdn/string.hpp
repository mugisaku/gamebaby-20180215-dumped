#ifndef LIBGBDN_string_HPP
#define LIBGBDN_string_HPP


#include<cstddef>
#include<utility>


namespace gbdn{
namespace gbdn_types{


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


  const char*  m_pointer;

  size_t  m_length;

public:
  constexpr string_view(const char*  p=nullptr) noexcept:
  m_pointer(p),
  m_length(p? get_length(p,0):0){}

  constexpr string_view(const char*  p, size_t  l) noexcept:
  m_pointer(p),
  m_length(l){}


  constexpr operator bool() const noexcept{return m_pointer;}

  constexpr bool  operator==(const char*  s) const noexcept{return compare(m_pointer,s,m_length);}

  constexpr bool  operator==(const string_view&  rhs) const noexcept
  {
    return(m_length == rhs.m_length) && compare(m_pointer,rhs.m_pointer,m_length);
  }

  constexpr const char&  operator[](int  i) const noexcept{return m_pointer[i];}

  constexpr const char*  get_data() const noexcept{return m_pointer;}

  constexpr size_t  get_length() const noexcept{return m_length;}

  constexpr const char*  begin() const noexcept{return m_pointer       ;}
  constexpr const char*    end() const noexcept{return m_pointer+m_length;}

};


class
string
{
  static char  null;

  char*  m_data=&null;

  size_t  m_length=0;

  value*  m_value=nullptr;

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

  const char*  get_data() const noexcept{return m_data;}
  size_t  get_length() const noexcept{return m_length;}

  string_view  get_view() const noexcept{return string_view(m_data,m_length);}

  const char*  begin() const noexcept{return m_data       ;}
  const char*    end() const noexcept{return m_data+m_length;}

  void          set_value(value*  v) noexcept;
  const value*  get_value() const noexcept{return m_value;}

  void  print(int  indent=0) const noexcept;

};


}


using string = gbdn_types::string;
using string_view = gbdn_types::string_view;


}




#endif




