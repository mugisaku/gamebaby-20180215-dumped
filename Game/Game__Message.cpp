#include"Game_private.hpp"




namespace gmbb{


namespace{


constexpr Point  message_point(8,160);

constexpr uint32_t  key_flags = flags_of_input::p_button;

MessageWindow*
window;

bool
is_finished;

bool
has_choosing;


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
  pop_routine();
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
    if(ctrl.test(p_button))
    {
        if(is_finished)
        {
            if(has_choosing)
            {
              start_choosing();
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
      window = new MessageWindow(glset,36,4,message_point);
    }


  task_list::push(*window);

  window->set_state(WindowState::full_opened);
}


void
close_message_window() noexcept
{
    if(window)
    {
      task_list::erase(*window);

      close_choosing_window();
    }
}


void
start_message(char const*  text, bool  cleaning) noexcept
{
  open_message_window();

    if(cleaning)
    {
      window->clear();
    }


  window->push(text);

  is_finished = false;

  has_choosing = false;


  push_routine(process);
}


void
start_message_with_choosing(char const*  text, std::initializer_list<char const*>  ls, bool  cleaning) noexcept
{
  open_message_window();

    if(cleaning)
    {
      window->clear();
    }


  window->push(text);

  prepare_choosing_window(ls,message_point+Point(248,24));

  is_finished = false;

  has_choosing = true;

  push_routine(process,return_);
}


}




