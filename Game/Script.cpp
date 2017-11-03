#include"Script.hpp"


namespace gmbb{




Script::
Script(gamn::List const&  ls) noexcept:
number(ls.size())
{
            table = new ScriptElement[number];
  auto  e = table                            ;

    for(auto&  v: ls)
    {
      *e++ = ScriptElement(v);
    }
}




void
Script::
clear() noexcept
{
  delete[] table          ;
           table = nullptr;

  number = 0;
}


void
Script::
print() const noexcept
{
  printf("{\n");

    for(auto&  e: *this)
    {
      e.print();

      printf("\n");
    }


  printf("}\n");
}


}




