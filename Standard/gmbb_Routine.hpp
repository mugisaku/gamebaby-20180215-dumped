#ifndef GMBB_Routine_HPP
#define GMBB_Routine_HPP


#include"gmbb_Controller.hpp"
#include"Pointer.hpp"
#include"FixedString.hpp"


namespace gmbb{


namespace coprocesses{


using coreturn = void  (*)(int  value);
using callback = void  (*)();


class
coprocess
{
  const char*  m_label="";

  callback  m_initialize=nullptr;
  callback        m_step=nullptr;

public:
  coprocess(const char*  label, callback  init, callback  step) noexcept:
  m_label(label),
  m_initialize(init),
  m_step(step){}

  const char*  get_label() const noexcept{return m_label;}
  callback      get_step() const noexcept{return m_step;}

  void  initialize() const noexcept
  {
      if(m_initialize)
      {
        m_initialize();
      }
  }

};


void  push(coreturn  ret, const coprocess&  proc) noexcept;

void   pop(      ) noexcept;
void   pop(int  v) noexcept;

void  wait_until_button_is_released() noexcept;

void  call() noexcept;


}


using coprocesses::coprocess;


}




#endif




