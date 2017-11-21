#include"Battle.hpp"
#include"SystemData.hpp"




namespace gmbb{


namespace{


FixedString
label("battle");


void
step(Controller const&  ctrl) noexcept
{
}


}


void
start_battle(coreturn_t  ret) noexcept
{
//  system_data::root_task.push(window);

  push_routine(label.pointer,step,ret);
}


}




