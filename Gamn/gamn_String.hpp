#ifndef GAMN_String_HPP
#define GAMN_String_HPP


#include<cstddef>
#include<utility>


namespace gamn{


class Value;


class
String
{
  static char  null;

  char*  data=&null;

  size_t  length=0;

  Value*  value=nullptr;

public:
  String() noexcept{}
  String(const char*  str, size_t  len, Value*  v=nullptr) noexcept{assign(str,len,v);}
  String(const String&   rhs) noexcept{*this = rhs;}
  String(      String&&  rhs) noexcept{*this = std::move(rhs);}
 ~String(){clear();}

  String&  operator=(const String&   rhs) noexcept;
  String&  operator=(      String&&  rhs) noexcept;

  bool  operator==(const char*  s) const noexcept;

  void  clear() noexcept;

  bool  compare(size_t  len, const char*  str) const noexcept;

  void  assign(const char*  str, size_t  len, Value*  v=nullptr) noexcept;

  const char*  get_data() const noexcept{return data;}
  size_t  get_length() const noexcept{return length;}

  void          set_value(Value*  v) noexcept;
  const Value*  get_value() const noexcept{return value;}

  void  print(int  indent=0) const noexcept;

};


}




#endif




