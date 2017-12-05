#ifndef GAMN_Value_HPP
#define GAMN_Value_HPP


#include"gamn_String.hpp"
#include<new>


namespace gamn{


enum class
ValueKind
{
  null,
  string,
  integer,
  real,
  list,

};


class List;


union
ValueData
{
  int        integer;
  double        real;
  String      string;
  List*         list;

   ValueData(){}
  ~ValueData(){}

};


class
Value
{
  ValueKind  kind=ValueKind::null;
  ValueData  data;

public:
  Value() noexcept{}
  Value(int        i) noexcept: kind(ValueKind::integer){data.integer = i;}
  Value(double     r) noexcept: kind(ValueKind::real   ){data.real    = r;}
  Value(String&&   s) noexcept: kind(ValueKind::string ){new(&data) String(std::move(s));}
  Value(List*           ls) noexcept: kind(ValueKind::list){data.list = ls;}
  Value(const Value&   rhs) noexcept{*this = rhs;}
  Value(      Value&&  rhs) noexcept{*this = std::move(rhs);}
 ~Value(){clear();}

  Value&  operator=(const Value&   rhs) noexcept;
  Value&  operator=(      Value&&  rhs) noexcept;

  operator bool() const noexcept{return kind != ValueKind::null;}

  bool  operator==(ValueKind  k) const noexcept{return kind == k;}

  Value&  neg() noexcept;


  bool  is_integer() const noexcept{return(kind == ValueKind::integer);}
  bool  is_real(   ) const noexcept{return(kind == ValueKind::real   );}
  bool  is_string( ) const noexcept{return(kind == ValueKind::string );}
  bool  is_list(   ) const noexcept{return(kind == ValueKind::list   );}

  ValueKind  get_kind() const noexcept{return kind;}

  void  clear() noexcept;

  int                  get_integer() const noexcept;
  double               get_real() const noexcept;
  const String&      get_string() const noexcept;
  const List&          get_list() const noexcept;

  void  print(int  indent=0) const noexcept;

};


}




#endif




