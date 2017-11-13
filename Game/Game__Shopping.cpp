#include"Game_private.hpp"
#include"EventQueue.hpp"
#include"ShopManager.hpp"




namespace gmbb{


namespace{


Return
final_retcb;




void  return_from_shop_menu(int  retval) noexcept;


void
return_from_message_of_continue_to_buy(int  retval) noexcept
{
  start_shop_menu(return_from_shop_menu);
}


void
return_from_message_of_when_money_is_enough(int  retval) noexcept
{
  start_message("continue_to_buy",return_from_message_of_continue_to_buy);
}


void
return_from_message_of_confirm_commodity_for_buy(int  retval) noexcept
{
  start_message("when_money_is_enough",return_from_message_of_when_money_is_enough);
}


void
return_from_shop_menu(int  retval) noexcept
{
  auto  shop = get_current_shop();

    if(retval >= 0)
    {
      auto&  comm = shop->get_commodity(retval);

      environment::set_value("chosen_commodity",comm.name.data());

      Event  evt(EventKind::shop_Buy_item);

      evt.shop.commodity = &comm;

      event_queue::push(evt);


      start_message("confirm_commodity_for_buy",return_from_message_of_confirm_commodity_for_buy);
    }

  else
    {
      Event  evt(EventKind::shop_Exit);

      event_queue::push(evt);


      close_shop_menu_window();


      start_message("on_exit",final_retcb);
    }
}


void
return_from_message_of_on_enter(int  retval) noexcept
{
  start_shop_menu(return_from_shop_menu);
}


}


void
start_shopping(char const*  label, Return  retcb) noexcept
{
    if(change_current_shop(label))
    {
      Event  evt(EventKind::shop_Enter);

      event_queue::push(evt);

      final_retcb = retcb;

      start_message("on_enter",return_from_message_of_on_enter);
    }
}


}




