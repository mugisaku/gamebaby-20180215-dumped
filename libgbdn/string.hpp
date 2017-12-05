#ifndef LIBGBDN_string_HPP
#define LIBGBDN_string_HPP


#include<cstddef>
#include<utility>


namespace gbdn{


class value;


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

  bool  operator==(const char*  s) const noexcept;

  void  clear() noexcept;

  bool  compare(size_t  len, const char*  str) const noexcept;

  void  assign(const char*  str, size_t  len, value*  v=nullptr) noexcept;

  const char*  get_data() const noexcept{return data;}
  size_t  get_length() const noexcept{return length;}

  void          set_value(value*  v) noexcept;
  const value*  get_value() const noexcept{return companion_value;}

  void  print(int  indent=0) const noexcept;

};


}




#endif




