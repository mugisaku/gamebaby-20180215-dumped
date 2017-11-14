#include"Game_private.hpp"
#include"EventQueue.hpp"
#include"Messembly_ImageBuilder.hpp"




namespace gmbb{


using namespace gamn;


namespace{


constexpr Point   message_point(8,160);
constexpr Point  choosing_point = message_point+Point(200,24);


messembly::Machine
m;


MessageWindow*
window;


void
return_for_choosing(int  retval) noexcept
{
    if(retval >= 0)
    {
      m.set_chosen_value(retval);
    }


  close_choosing_window();
}


void
proc_cb(messembly::Machine&  m, const std::string&  text)
{
  using namespace messembly;

  static bool  flag;

      switch(m.get_opcode())
      {
    case(Opcode::ttx):
        window->push(text.data());
        break;
    case(Opcode::adb):
          if(!flag)
          {
            prepare_choosing_window({},choosing_point);

            flag = true;
          }


        append_answer(text.data());
        break;
    case(Opcode::xch):
        flag = false;

        start_choosing(Avoidable(false),return_for_choosing);
        break;
    case(Opcode::xfn):
        process_string(m,text);
        break;
      }
}


void
operate_message(Controller const&  ctrl) noexcept
{
    if(window->is_stopped())
    {
        if(ctrl.is_p_button_pressing())
        {
          window->scroll();

          return;
        }
    }


  auto  now = ctrl.get_time();

  constexpr uint32_t  interval_time_base = 40;

  auto  interval_time = interval_time_base;

  static uint32_t  last_time;

    if(ctrl.is_p_button_pressing())
    {
      interval_time /= 10;
    }


    if(now > (last_time+interval_time))
    {
      last_time = now;

      window->step();
    }
}


void
return_for_shopping(int  retval) noexcept
{
    if(retval >= 0)
    {
    }


  close_shop_menu_window();
}


void
process(Controller const&  ctrl) noexcept
{
    if(window->is_remaining())
    {
      operate_message(ctrl);
    }

  else
    if(!m.is_halted())
    {
      m.step();
    }

  else
    {
      pop_routine();
    }
}


}


void
open_message_window() noexcept
{
    if(!window)
    {
      window = new MessageWindow(glset,24,4,message_point);

      m.set_process_callback(proc_cb);
    }


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
    if(window)
    {
      window->clear();
    }
}


bool
is_message_window_opened() noexcept
{
  return window && window->get_group();
}




bool
is_message_window_clean() noexcept
{
  return window && window->is_clean();
}


void
start_message(char const*  label, Return  retcb) noexcept
{
  Event  evt(EventKind::message_Start);

  evt.message.content = label;

  event_queue::push(evt);

  reset_machine(m,label);

  open_message_window();

    if(window->is_stopped())
    {
      window->scroll();
    }


  push_routine(process,retcb);
}


}




