#include"gamn_Value.hpp"
#include"gamn_List.hpp"




namespace gamn{




Value&
Value::
operator=(Value&&  rhs) noexcept
{
  clear();

  std::swap(kind,rhs.kind);
  std::swap(name,rhs.name);

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
  case(ValueKind::value):
      data.value = rhs.data.value;
      break;
  case(ValueKind::list):
      data.list = rhs.data.list;
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
  name = rhs.name;

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
  case(ValueKind::value):
      data.value = new Value(rhs.data.value);
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
  name.clear();

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
  case(ValueKind::value):
      delete data.value;
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
Value const&         Value::get_value() const noexcept{return *data.value;}
List const&          Value::get_list() const noexcept{return *data.list;}




void
Value::
print() const noexcept
{
    if(*this)
    {
        if(name.size())
        {
          printf("<\"%s\":",name.data());
        }


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
      case(ValueKind::value):
          data.value->print();
          break;
      case(ValueKind::list):
          data.list->print();
          break;
        }


        if(name.size())
        {
          printf(">");
        }
    }

  else
    {
      printf("(null)");
    }
}




}




