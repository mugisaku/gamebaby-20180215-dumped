#include"gamn_String.hpp"
#include"gamn_Value.hpp"
#include<cstring>
#include<cstdio>
#include<utility>




namespace gamn{




char
String::
null;




String&
String::
operator=(const String&   rhs) noexcept
{
  clear();

  assign(rhs.data,rhs.length,rhs.value? new Value(*rhs.value):nullptr);

  return *this;
}


String&
String::
operator=(String&&  rhs) noexcept
{
  clear();

  length = rhs.length;

  std::swap( data,rhs.data );
  std::swap(value,rhs.value);

  return *this;
}


bool
String::
operator==(const char*  s) const noexcept
{
  return(std::strcmp(data,s) == 0);
}




void
String::
clear() noexcept
{
    if(data != &null)
    {
      delete[] data        ;
               data = &null;
    }


  length = 0;

  delete value          ;
         value = nullptr;
}


bool
String::
compare(size_t  len, const char*  str) const noexcept
{
  return(length == len) && (std::memcpy(data,str,len) == 0);
}


void
String::
assign(const char*  str, size_t  len, Value*  v) noexcept
{
  clear();

  length = len;

  data = new char[length+1];

  std::memcpy(data,str,length);

  data[length] = 0;

  value = v;
}


void
String::
set_value(Value*  v) noexcept
{
  delete value    ;
         value = v;
}


void
String::
print(int  indent) const noexcept
{
  printf("\"%s\"",data);

    if(value)
    {
      printf(":");

      value->print(indent);
    }
}


}




