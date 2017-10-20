#ifndef GMBB_Routine_HPP
#define GMBB_Routine_HPP


#include"gmbb_Controller.hpp"


namespace gmbb{


struct
Routine
{
  using OnStepCallback   = void  (*)(Controller const&  ctrl);
  using OnReturnCallback = void  (*)(int  value);

  OnStepCallback      on_step;
  OnReturnCallback  on_return;

  constexpr Routine(OnStepCallback  st, OnReturnCallback  ret) noexcept:
  on_step(st),
  on_return(ret){}

};


void  push_routine(Routine::OnStepCallback  st, Routine::OnReturnCallback  ret=nullptr) noexcept;

void   pop_routine(      ) noexcept;
void   pop_routine(int  v) noexcept;

void  wait_until_button_is_released() noexcept;

void  call_routine(Controller const&  ctrl) noexcept;


}




#endif




