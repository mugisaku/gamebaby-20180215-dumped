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

  } m_kind;


  union data_type{
    int         i;
    double      r;
    string      s;
    list*      ls;

     data_type(){}
    ~data_type(){}

  } m_data;

public:
  value() noexcept{}
  value(int        i) noexcept: m_kind(kind_type::integer){m_data.i = i;}
  value(double     r) noexcept: m_kind(kind_type::real   ){m_data.r = r;}
  value(string&&   s) noexcept: m_kind(kind_type::string ){new(&m_data) string(std::move(s));}
  value(list*           ls) noexcept: m_kind(kind_type::list){m_data.ls = ls;}
  value(const value&   rhs) noexcept{*this = rhs;}
  value(      value&&  rhs) noexcept{*this = std::move(rhs);}
 ~value(){clear();}

  value&  operator=(const value&   rhs) noexcept;
  value&  operator=(      value&&  rhs) noexcept;

  operator bool() const noexcept{return m_kind != kind_type::null;}


  bool  is_integer() const noexcept{return(m_kind == kind_type::integer);}
  bool  is_real(   ) const noexcept{return(m_kind == kind_type::real   );}
  bool  is_string( ) const noexcept{return(m_kind == kind_type::string );}
  bool  is_list(   ) const noexcept{return(m_kind == kind_type::list   );}

  void  clear() noexcept;

  int               get_integer() const noexcept;
  double               get_real() const noexcept;
  const string&      get_string() const noexcept;
  const list&          get_list() const noexcept;

  void  print(int  indent=0) const noexcept;

};


}




#endif




