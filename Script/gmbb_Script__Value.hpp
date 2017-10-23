#ifndef GMBB_Script__Value_HPP
#define GMBB_Script__Value_HPP


#include<string>
#include<cstdio>
#include<new>


namespace gmbb{
namespace script{


enum class
ValueKind
{
  null,
  string,
  integer,
  real,
  value,
  list,

};


class Value;
class  List;


union
ValueData
{
  int          integer;
  double          real;
  std::string   string;
  Value*         value;
  List*           list;

   ValueData(){}
  ~ValueData(){}

};


class
ValueTag
{
  std::string  name;

  ValueKind  kind;

public:
  ValueTag(ValueKind  k, char const*  s) noexcept:
  name(s),
  kind(k){}

  ValueKind  get_kind() const noexcept{return kind;}
  std::string const&  get_name() const noexcept{return name;}


};


class
Value
{
  std::string  name;

  ValueKind  kind=ValueKind::null;
  ValueData  data;

public:
  Value() noexcept{}
  Value(int              i) noexcept: kind(ValueKind::integer){data.integer = i;}
  Value(double           r) noexcept: kind(ValueKind::real   ){data.real    = r;}
  Value(std::string&&    s) noexcept: kind(ValueKind::string ){new(&data) std::string(std::move(s));}
  Value(Value*           v) noexcept: kind(ValueKind::value  ){data.value = v;}
  Value(List*           ls) noexcept: kind(ValueKind::list   ){data.list = ls;}
  Value(Value const&  rhs) noexcept{*this = rhs;}
  Value(Value&&       rhs) noexcept{*this = std::move(rhs);}
 ~Value(){clear();}

  Value&  operator=(Value const&  rhs) noexcept;
  Value&  operator=(Value&&       rhs) noexcept;

  operator bool() const noexcept{return kind != ValueKind::null;}

  bool  operator==(std::string const&  name_) const noexcept{return name == name_;}
  bool  operator==(ValueKind  k) const noexcept{return kind == k;}
  bool  operator==(ValueTag  tag) const noexcept{return is(tag.get_kind(),tag.get_name());}

  Value&  neg() noexcept;


  bool  is(ValueKind  k, std::string const&  name_) const noexcept{return (*this == k) && (*this == name_);}
  bool  is_integer(std::string const&  name_) const noexcept{return is(ValueKind::integer,name_);}
  bool  is_real(   std::string const&  name_) const noexcept{return is(ValueKind::real   ,name_);}
  bool  is_string( std::string const&  name_) const noexcept{return is(ValueKind::string ,name_);}
  bool  is_value(  std::string const&  name_) const noexcept{return is(ValueKind::value  ,name_);}
  bool  is_list(   std::string const&  name_) const noexcept{return is(ValueKind::list   ,name_);}

  ValueKind  get_kind() const noexcept{return kind;}

  void  set_name(std::string&&  new_name) noexcept{name = std::move(new_name);}
  std::string const&  get_name() const noexcept{return name;}

  void  clear() noexcept;

  int                  get_integer() const noexcept;
  double               get_real() const noexcept;
  std::string const&   get_string() const noexcept;
  Value const&         get_value() const noexcept;
  List const&          get_list() const noexcept;

  void  print() const noexcept;

};




}}




#endif




