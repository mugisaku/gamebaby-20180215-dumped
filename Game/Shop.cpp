#include"Shop.hpp"


namespace gmbb{




Shop::
Shop(std::string const&  name_, script::List const&  ls) noexcept:
name(name_)
{
    for(auto&  v: ls)
    {
        if(v.is_list("commodity"))
        {
          read(v.get_list().get_first());
        }
    }
}




void
Shop::
read(script::ListNode const*  cur) noexcept
{
  Commodity  comm;

    while(cur)
    {
      auto&  v = cur->value;

      cur = cur->next;

        if(v.is_string("name"))
        {
          comm.name = v.get_string();
        }

      else
        if(v.is_integer("price"))
        {
          comm.price = Price(v.get_integer());
        }

      else
        if(v.is_integer("number"))
        {
          comm.number = v.get_integer();
        }
    }


  push(comm);
}


}




