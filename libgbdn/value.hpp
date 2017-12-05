#ifndef LIBGBDN_value_HPP
#define LIBGBDN_value_HPP


#include"string.hpp"
#include<new>


namespace gbdn{


class list;


class
value
{
  enum class kind_type{
    null,
    string,
    integer,
    real,
    list,

  } kind;


  union data_type{
    int         i;
    double      r;
    string      s;
    list*      ls;

     data_type(){}
    ~data_type(){}

  } data;

public:
  value() noexcept{}
  value(int        i) noexcept: kind(kind_type::integer){data.i = i;}
  value(double     r) noexcept: kind(kind_type::real   ){data.r = r;}
  value(string&&   s) noexcept: kind(kind_type::string ){new(&data) string(std::move(s));}
  value(list*           ls) noexcept: kind(kind_type::list){data.ls = ls;}
  value(const value&   rhs) noexcept{*this = rhs;}
  value(      value&&  rhs) noexcept{*this = std::move(rhs);}
 ~value(){clear();}

  value&  operator=(const value&   rhs) noexcept;
  value&  operator=(      value&&  rhs) noexcept;

  operator bool() const noexcept{return kind != kind_type::null;}


  bool  is_integer() const noexcept{return(kind == kind_type::integer);}
  bool  is_real(   ) const noexcept{return(kind == kind_type::real   );}
  bool  is_string( ) const noexcept{return(kind == kind_type::string );}
  bool  is_list(   ) const noexcept{return(kind == kind_type::list   );}

  void  clear() noexcept;

  int               get_integer() const noexcept;
  double               get_real() const noexcept;
  const string&      get_string() const noexcept;
  const list&          get_list() const noexcept;

  void  print(int  indent=0) const noexcept;

};


}




#endif




