#include"gmbb_Routine.hpp"
#include"Pointer.hpp"
#include<vector>




namespace gmbb{


namespace{


struct
Routine
{
  const Pointer<const char>  label;

    costep_t const    costep;
  coreturn_t const  coreturn;

  constexpr Routine(Pointer<const char>  label_, costep_t  st, coreturn_t  ret) noexcept:
  label(label_),
  costep(st),
  coreturn(ret){}

};


constexpr uint32_t  key_flags = (Controller::p_button_flag|
                                 Controller::n_button_flag);


uint32_t
flags;


int
returned_value;


std::vector<Routine>
stack;


}




void
push_routine(Pointer<const char>  label, costep_t  st, coreturn_t  ret) noexcept
{
  stack.emplace_back(label,st,ret);

  wait_until_button_is_released();
}


void
pop_routine(Pointer<const char>  label) noexcept
{
  static FixedString  base("[pop_routine error]");


    if(stack.size())
    {
      auto  r = stack.back();

        if(r.label == label)
        {
          auto  ret = r.coreturn;

          stack.pop_back();

          wait_until_button_is_released();

            if(ret)
            {
              ret(returned_value);
            }
        }

      else
        {
          printf("%s %s != %s",base.pointer,r.label,label);
        }
    }

  else
    {
      printf("%s has no stack in %s from %s\n",base.pointer,label);
    }
}


void
pop_routine(Pointer<const char>  label, int  v) noexcept
{
  returned_value = v;

  pop_routine(label);
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
        if(stack.size())
        {
          stack.back().costep(ctrl);
        }

      else
        {
          printf("[call_routine error] have no stack\n");
        }
    }
}




}




