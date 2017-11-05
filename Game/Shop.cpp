#include"Shop.hpp"


namespace gmbb{




Shop::
Shop(std::string const&  name_, gamn::List const&  ls) noexcept:
name(name_)
{
    for(auto&  v: ls)
    {
        if(v.is_list("commodity"))
        {
          read_commodity(v.get_list().get_first());
        }

      else
        if(v.is_list("on_enter"))
        {
          message_set.on_enter = v.get_list().get_first();
        }

      else
        if(v.is_list("on_exit"))
        {
          message_set.on_exit = v.get_list().get_first();
        }

      else
        if(v.is_list("confirm_commodity_for_buy"))
        {
          message_set.confirm_commodity_for_buy = v.get_list().get_first();
        }

      else
        if(v.is_list("when_money_is_enough"))
        {
          message_set.when_money_is_enough = v.get_list().get_first();
        }

      else
        if(v.is_list("when_money_is_not_enough"))
        {
          message_set.when_money_is_not_enough = v.get_list().get_first();
        }

      else
        if(v.is_list("continue_to_buy"))
        {
          message_set.continue_to_buy = v.get_list().get_first();
        }
    }
}




void
Shop::
read_commodity(gamn::ListNode const*  cur) noexcept
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




