#ifndef GMBB_Routine_HPP
#define GMBB_Routine_HPP


#include"gmbb_Controller.hpp"
#include"Pointer.hpp"
#include"FixedString.hpp"


namespace gmbb{


using   costep_t = void  (*)(Controller const&  ctrl);
using coreturn_t = void  (*)(int  value);


void  push_routine(ro_ptr<char>  label, costep_t  st, coreturn_t  ret=nullptr) noexcept;

void   pop_routine(ro_ptr<char>  label        ) noexcept;
void   pop_routine(ro_ptr<char>  label, int  v) noexcept;

void  wait_until_button_is_released() noexcept;

void  call_routine(Controller const&  ctrl) noexcept;


}




#endif




