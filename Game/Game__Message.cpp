#include"Game_private.hpp"




namespace gmbb{


using namespace script;


namespace{


constexpr Point   message_point(8,160);
constexpr Point  choosing_point = message_point+Point(200,24);

constexpr uint32_t  key_flags = flags_of_input::p_button;


Cursor
cursor;


ListNode const*
candidates[8];


MessageWindow*
window;

bool
is_finished;

bool
has_choosing;


void
clear_candidates() noexcept
{
    for(auto&  cd: candidates)
    {
      cd = nullptr;
    }
}


void
operate_message(Controller const&  ctrl) noexcept
{
  using namespace gmbb::flags_of_input;

    if(window->is_stopped())
    {
        if(ctrl.test(p_button))
        {
          window->scroll();

          return;
        }
    }


  auto  now = ctrl.get_time();

  constexpr uint32_t  interval_time_base = 40;

  auto  interval_time = interval_time_base;

  static uint32_t  last_time;

    if(ctrl.test(p_button))
    {
      interval_time /= 5;
    }


    if(now > (last_time+interval_time))
    {
      last_time = now;

      window->step();
    }
}


void
make_choosing(ListNode const*  cur) noexcept
{
  has_choosing = true;

  prepare_choosing_window({},choosing_point);

  clear_candidates();

  ListNode const**  it = candidates;

    while(cur)
    {
      auto&  v = cur->value;

        if(v == ValueKind::list)
        {
          append_answer(v.get_name().data());

          *it++ = v.get_list().get_first();
        }


      cur = cur->next;
    }
}


void
read_next_line() noexcept
{
  auto&  v = *cursor;

  cursor.advance();

    if(v == script::ValueKind::string)
    {
      window->push(v.get_string().data());
    }

  else
    if(v.is_list("choosing"))
    {
      make_choosing(v.get_list().get_first());
    }

  else
    if(v.is_value("call_shop"))
    {
      auto&  cov = v.get_value();

        if(cov.is_string("shop_name"))
        {
          auto  sc = find_gson("shop",cov.get_string().data());

            if(sc)
            {
              auto  cur = sc->get_list().get_first();

                while(cur)
                {
                  auto&  v = cur->value;

                  cur = cur->next;

                    if(v.is_list("commodity"))
                    {
                      	shop::read(v.get_list().get_first());
                    }
                }


              start_shop_menu([](int  retval){close_shop_menu_window();});
            }
        }
    }

  else
    if(v)
    {
      printf("[message error] processable value...");

      v.print();

      printf("\n");

      fflush(stdout);
    }
}


void
return_(int  retval) noexcept
{
    if(retval >= 0)
    {
      auto  nd = candidates[retval];

        if(nd)
        {
          cursor.go_in(nd);

          window->clear();

          clear_candidates();

          is_finished = false;
        }

      else
        {
          pop_routine();
        }
    }

  else
    {
      pop_routine();
    }


  close_choosing_window();

  has_choosing = false;
}


void
process(Controller const&  ctrl) noexcept
{
  using namespace gmbb::flags_of_input;

    if(window->is_remaining())
    {
      operate_message(ctrl);
    }

  else
    if(cursor)
    {
      read_next_line();
    }

  else
    if(ctrl.test(p_button))
    {
        if(is_finished)
        {
            if(has_choosing)
            {
              start_choosing(false,return_);
            }

          else
            {
              pop_routine();
            }
        }

      else
        {
          is_finished = true;

          wait_until_button_is_released();
        }
    }

  else
    {
      is_finished = true;
    }
}


}


void
open_message_window() noexcept
{
    if(!window)
    {
      window = new MessageWindow(glset,24,4,message_point);
    }


  clear_candidates();

  root_task.push(*window);

  window->set_state(WindowState::full_opened);
}


void
close_message_window() noexcept
{
    if(window)
    {
      root_task.erase(*window);

      close_choosing_window();
    }
}


void
clear_message_window() noexcept
{
  window->clear();
}


void
start_message(char const*  text, Return  retcb) noexcept
{
  open_message_window();

  clear_message_window();

  window->push(text);

  is_finished = false;

  has_choosing = false;


  push_routine(process,retcb);
}


void
start_message(script::ListNode const*  nd, Return  retcb) noexcept
{
  open_message_window();

  clear_message_window();

  cursor = Cursor(nd);

  clear_candidates();

  is_finished = false;

  has_choosing = false;


  push_routine(process,retcb);
}


void
start_message_with_choosing(char const*  text, std::initializer_list<char const*>  ls, Return  retcb) noexcept
{
  open_message_window();

  clear_message_window();

  clear_candidates();

  window->push(text);

  prepare_choosing_window(ls,choosing_point);

  is_finished = false;

  has_choosing = true;

  push_routine(process,retcb);
}


}




