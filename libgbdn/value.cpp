#include"gamn_Value.hpp"
#include"gamn_List.hpp"
#include"gamn_String.hpp"
#include<cstdio>




namespace gamn{




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
      new(&data) String(std::move(rhs.data.string));
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
    }


  return *this;
}


Value&
Value::
operator=(const Value&  rhs) noexcept
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
  case(ValueKind::null):
      break;
  case(ValueKind::string):
      new(&data) String(rhs.data.string);
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
      data.string.~String();
      break;
  case(ValueKind::integer):
  case(ValueKind::real):
      break;
  case(ValueKind::list):
      delete data.list;
      break;
    }


  kind = ValueKind::null;
}





int            Value::get_integer() const noexcept{return data.integer;}
double            Value::get_real() const noexcept{return data.real;}
const String&   Value::get_string() const noexcept{return data.string;}
const List&       Value::get_list() const noexcept{return *data.list;}




void
Value::
print(int  indent) const noexcept
{
    switch(kind)
    {
  case(ValueKind::null):
      printf("(null)");
      break;
  case(ValueKind::string):
      data.string.print(indent);
      break;
  case(ValueKind::integer):
      printf("%d",data.integer);
      break;
  case(ValueKind::real):
      printf("%f",data.real);
      break;
  case(ValueKind::list):
      data.list->print(indent);
      break;
    }
}




}




