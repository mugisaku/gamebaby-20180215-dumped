#include"value.hpp"
#include"list.hpp"
#include"string.hpp"
#include<cstdio>




namespace gbdn{




value&
value::
operator=(value&&  rhs) noexcept
{
  clear();

  std::swap(kind,rhs.kind);

    switch(kind)
    {
  case(kind_type::null):
      break;
  case(kind_type::string):
      new(&data) string(std::move(rhs.data.s));
      break;
  case(kind_type::integer):
      data.i = rhs.data.i;
      break;
  case(kind_type::real):
      data.r = rhs.data.r;
      break;
  case(kind_type::list):
      data.ls = rhs.data.ls;
      break;
    }


  return *this;
}


value&
value::
operator=(const value&  rhs) noexcept
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
  case(kind_type::null):
      break;
  case(kind_type::string):
      new(&data) string(rhs.data.s);
      break;
  case(kind_type::integer):
      data.i = rhs.data.i;
      break;
  case(kind_type::real):
      data.r = rhs.data.r;
      break;
  case(kind_type::list):
      data.ls = new list(*rhs.data.ls);
      break;
    }


  return *this;
}




void
value::
clear() noexcept
{
    switch(kind)
    {
  case(kind_type::null):
      break;
  case(kind_type::string):
      data.s.~string();
      break;
  case(kind_type::integer):
  case(kind_type::real):
      break;
  case(kind_type::list):
      delete data.ls;
      break;
    }


  kind = kind_type::null;
}





int            value::get_integer() const noexcept{return data.i;}
double            value::get_real() const noexcept{return data.r;}
const string&   value::get_string() const noexcept{return data.s;}
const list&       value::get_list() const noexcept{return *data.ls;}




void
value::
print(int  indent) const noexcept
{
    switch(kind)
    {
  case(kind_type::null):
      printf("(null)");
      break;
  case(kind_type::string):
      data.s.print(indent);
      break;
  case(kind_type::integer):
      printf("%d",data.i);
      break;
  case(kind_type::real):
      printf("%f",data.r);
      break;
  case(kind_type::list):
      data.ls->print(indent);
      break;
    }
}




}




