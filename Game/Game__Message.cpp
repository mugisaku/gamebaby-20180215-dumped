#include"Game_private.hpp"
#include"Script.hpp"
#include"EventQueue.hpp"




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
}


void
read_next_line() noexcept
{
  auto&  v = *cursor;

  cursor.advance();

    if(v.is_string("text"))
    {
      window->push(v.get_string().data());
    }

  else
    if(v.is_string())
    {
      auto  s = v.get_string();

           if(s == "clear"){window->clear();}
      else if(s == "exit"){pop_routine();}
    }

  else
    if(v.is_list("choosing"))
    {
      cursor.go_in(v.get_list().get_first());

      prepare_choosing_window({},choosing_point);

      clear_candidates();

      ListNode const**  it = candidates;

        while(cursor)
        {
          auto&  v = *cursor;

          cursor.advance(Cursor::GoUpIfReachedEnd(false));

            if(v.is_value("entry"))
            {
              auto&  vv = v.get_value();

              append_answer(vv.get_name().data());

              *it++ = vv.get_list().get_first();
            }
        }


      start_choosing(Avoidable(false),return_);
    }

  else
    if(v.is_string("call_shop"))
    {
      close_main_menu_window();
        hide_status_reportor();

      start_shop_menu(v.get_string().data(),[](int  retval){close_shop_menu_window();});
    }

  else
    if(v)
    {
      printf("[message error] unprocessable value...");

      v.print();

      printf("\n");

      fflush(stdout);
    }
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
          pop_routine();
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
start_message(char const*  label, Return  retcb) noexcept
{
  auto  v = find_message_script(label);

    if(v && v->is_list())
    {
      Event  evt(EventKind::message_Start);

      evt.message.content = label;

      event_queue::push(evt);

Script(v->get_list()).print();
      start_message(v->get_list().get_first(),retcb);
    }

  else
    {
      printf("[start message error] \"%s\"というメッセージのデータはみつからない\n",label);
    }
}


void
start_message(script::ListNode const*  nd, Return  retcb) noexcept
{
  open_message_window();

  clear_message_window();

  cursor = Cursor(nd);

  clear_candidates();

  is_finished = false;


  push_routine(process,retcb);
}


}




