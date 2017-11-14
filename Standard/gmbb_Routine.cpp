#include"gmbb_Routine.hpp"
#include<vector>




namespace gmbb{


namespace{
constexpr uint32_t  key_flags = (Controller::p_button_flag|
                                 Controller::n_button_flag);


uint32_t
flags;


int
returned_value;


std::vector<Routine>
routine_stack;
}


void
push_routine(Routine::OnStepCallback  st, Routine::OnReturnCallback  ret) noexcept
{
  routine_stack.emplace_back(st,ret);

  wait_until_button_is_released();
}


void
pop_routine() noexcept
{
    if(routine_stack.size())
    {
      auto  ret = routine_stack.back().on_return;

      routine_stack.pop_back();

      wait_until_button_is_released();

        if(ret)
        {
          ret(returned_value);
        }
    }
}


void
pop_routine(int  v) noexcept
{
  returned_value = v;

  pop_routine();
}


void
wait_until_button_is_released() noexcept
{
  flags = 0xFFFFFFFF;
}


void
call_routine(Controller const&  ctrl) noexcept
{
  flags &= ctrl.get();

    if(!(flags&key_flags))
    {
      routine_stack.back().on_step(ctrl);
    }
}




}




