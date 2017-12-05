#include"string.hpp"
#include"value.hpp"
#include<cstring>
#include<cstdio>
#include<utility>




namespace gbdn{




char
string::
null;




string&
string::
operator=(const string&   rhs) noexcept
{
  clear();

  assign(rhs.data,rhs.length,rhs.companion_value? new value(*rhs.companion_value):nullptr);

  return *this;
}


string&
string::
operator=(string&&  rhs) noexcept
{
  clear();

  length = rhs.length;

  std::swap(           data,rhs.data           );
  std::swap(companion_value,rhs.companion_value);

  return *this;
}


bool
string::
operator==(const char*  s) const noexcept
{
  return(std::strcmp(data,s) == 0);
}




void
string::
clear() noexcept
{
    if(data != &null)
    {
      delete[] data        ;
               data = &null;
    }


  length = 0;

  delete companion_value          ;
         companion_value = nullptr;
}


bool
string::
compare(size_t  len, const char*  str) const noexcept
{
  return(length == len) && (std::memcmp(data,str,len) == 0);
}


void
string::
assign(const char*  str, size_t  len, value*  v) noexcept
{
  clear();

  length = len;

  data = new char[length+1];

  std::memcpy(data,str,length);

  data[length] = 0;

  companion_value = v;
}


void
string::
set_value(value*  v) noexcept
{
  delete companion_value    ;
         companion_value = v;
}


void
string::
print(int  indent) const noexcept
{
  printf("\"%s\"",data);

    if(companion_value)
    {
      printf(":");

      companion_value->print(indent);
    }
}


}




