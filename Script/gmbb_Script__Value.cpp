#include"gmbb_Script__Value.hpp"
#include"gmbb_Script__List.hpp"




namespace gmbb{
namespace script{




Value&
Value::
operator=(Value&&  rhs) noexcept
{
  clear();

  std::swap(kind,rhs.kind);

    switch(kind)
    {
  case(ValueKind::null):
      break;
  case(ValueKind::string):
      new(&data) std::string(std::move(rhs.data.string));
      break;
  case(ValueKind::integer):
      data.integer = rhs.data.integer;
      break;
  case(ValueKind::real):
      data.real = rhs.data.real;
      break;
  case(ValueKind::list):
      data.list = rhs.data.list;
      break;
  case(ValueKind::pair):
      data.pair = rhs.data.pair;
      break;
    }


  return *this;
}


Value&
Value::
operator=(Value const&  rhs) noexcept
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
  case(ValueKind::null):
      break;
  case(ValueKind::string):
      new(&data) std::string(rhs.data.string);
      break;
  case(ValueKind::integer):
      data.integer = rhs.data.integer;
      break;
  case(ValueKind::real):
      data.real = rhs.data.real;
      break;
  case(ValueKind::list):
      data.list = new List(*rhs.data.list);
      break;
  case(ValueKind::pair):
      data.pair = new Pair(*rhs.data.pair);
      break;
    }


  return *this;
}


Value&
Value::
neg() noexcept
{
    switch(kind)
    {
  case(ValueKind::integer):
      data.integer = -data.integer;
      break;
  case(ValueKind::real):
      data.real = -data.real;
      break;
  default:;
    }


  return *this;
}




void
Value::
clear() noexcept
{
    switch(kind)
    {
  case(ValueKind::null):
      break;
  case(ValueKind::string):
      data.string.~basic_string();
      break;
  case(ValueKind::integer):
  case(ValueKind::real):
      break;
  case(ValueKind::pair):
      delete data.pair;
      break;
  case(ValueKind::list):
      delete data.list;
      break;
    }


  kind = ValueKind::null;
}





int                  Value::get_integer() const noexcept{return data.integer;}
double               Value::get_real() const noexcept{return data.real;}
std::string const&   Value::get_string() const noexcept{return data.string;}
Pair const&          Value::get_pair() const noexcept{return *data.pair;}
List const&          Value::get_list() const noexcept{return *data.list;}




void
Value::
print() const noexcept
{
    switch(kind)
    {
  case(ValueKind::null):
      printf("(null)");
      break;
  case(ValueKind::string):
      printf("\"%s\"",data.string.data());
      break;
  case(ValueKind::integer):
      printf("%d",data.integer);
      break;
  case(ValueKind::real):
      printf("%f",data.real);
      break;
  case(ValueKind::pair):
      printf("%s:",data.pair->name.data());
      data.pair->value.print();
      break;
  case(ValueKind::list):
      data.list->print();
      break;
    }
}




}}




