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
  pair,
  list,

};


class Value;
class  List;
struct Pair;


union
ValueData
{
  int          integer;
  double          real;
  std::string   string;
  Pair*           pair;
  List*           list;

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
  Value(int              i) noexcept: kind(ValueKind::integer){data.integer = i;}
  Value(double           r) noexcept: kind(ValueKind::real   ){data.real    = r;}
  Value(std::string&&    s) noexcept: kind(ValueKind::string ){new(&data) std::string(std::move(s));}
  Value(Pair*           pa) noexcept: kind(ValueKind::pair   ){data.pair = pa;}
  Value(List*           ls) noexcept: kind(ValueKind::list   ){data.list = ls;}
  Value(Value const&  rhs) noexcept{*this = rhs;}
  Value(Value&&       rhs) noexcept{*this = std::move(rhs);}
 ~Value(){clear();}

  Value&  operator=(Value const&  rhs) noexcept;
  Value&  operator=(Value&&       rhs) noexcept;

  operator bool() const noexcept{return kind != ValueKind::null;}

  bool  operator==(ValueKind  k) const noexcept{return kind == k;}

  Value&  neg() noexcept;


  ValueKind  get_kind() const noexcept{return kind;}

  void  clear() noexcept;

  int                  get_integer() const noexcept;
  double               get_real() const noexcept;
  std::string const&   get_string() const noexcept;
  Pair const&          get_pair() const noexcept;
  List const&          get_list() const noexcept;

  void  print() const noexcept;

};


struct
Pair
{
  std::string  name;

  Value  value;

  Pair(std::string&&  name_, Value&&  value_) noexcept:
  name(std::move(name_)),
  value(std::move(value_)){}

};




}}




#endif




