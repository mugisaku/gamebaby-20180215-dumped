#include"gmbb_Routine.hpp"
#include<vector>




namespace gmbb{


namespace{
constexpr uint32_t  key_flags = (flags_of_input::p_button|flags_of_input::n_button);


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
      routine_stack.pop_back();

      wait_until_button_is_released();

        if(routine_stack.size())
        {
          auto  ret = routine_stack.back().on_return;

            if(ret)
            {
              ret(returned_value);
            }
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




