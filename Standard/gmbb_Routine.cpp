#include"gmbb_Routine.hpp"
#include"Pointer.hpp"
#include<vector>




namespace gmbb{
namespace coprocesses{


namespace{


class
element
{
  const char*  m_label;

  callback      m_step;
  coreturn  m_coreturn;

public:
  element(const char*  label, callback  step) noexcept:
  m_label(label),
  m_coreturn(nullptr),
  m_step(step){}

  void  step() noexcept{m_step();}

  const char*  get_label() const noexcept{return m_label;}

  void  set_coreturn(coreturn  ret) noexcept{m_coreturn = ret;}

  void  do_return(int  v) noexcept
  {
      if(m_coreturn)
      {
        m_coreturn(v);
      }
  }

};


constexpr uint32_t  key_flags = (Controller::p_button_flag|
                                 Controller::n_button_flag);


uint32_t
flags;


std::vector<element>
stack({element("base",[](){})});


int
returned_value;


bool
need_to_pop;


}




void
push(coreturn  ret, const coprocess&  proc) noexcept
{
    if(!need_to_pop)
    {
      stack.back().set_coreturn(ret);

      stack.emplace_back(proc.get_label(),proc.get_step());

      proc.initialize();

      wait_until_button_is_released();
    }

  else
    {
      printf("popが内部実行されるまで、pushできない\n");
    }
}


void
pop() noexcept
{
    if(!need_to_pop)
    {
      need_to_pop = true;
    }

  else
    {
      printf("連続でpopはできない\n");
    }
}


void
pop(int  v) noexcept
{
    if(!need_to_pop)
    {
      returned_value = v;

      need_to_pop = true;
    }

  else
    {
      printf("連続でpopはできない\n");
    }
}


void
wait_until_button_is_released() noexcept
{
  flags = 0xFFFFFFFF;
}


void
call() noexcept
{
    if(need_to_pop)
    {
        if(stack.size() <= 1)
        {
          printf("これ以上のpopはできない\n");
        }

      else
        {
          stack.pop_back();

          need_to_pop = false;

          stack.back().do_return(returned_value);
        }
    }


  flags &= ctrl.get();

    if(!(flags&key_flags))
    {
      stack.back().step();
    }
}




}}




