#include"EffectObject.hpp"




namespace gmbb{




void
EffectObject::
change_direction(Direction  d) noexcept
{
  previous_direction = direction    ;
                       direction = d;
}


void
EffectObject::
change_action_index(ActionIndex  i) noexcept
{
  action_index = i;

  pattern_index = 0;

  reset_frame_count();
  reset_motion_count();
}


bool
EffectObject::
check_visible_count() noexcept
{
    if(invisible_count)
    {
      --invisible_count;

      return false;
    }


    if(!invisible_count)
    {
        if(visible_count)
        {
          --visible_count;

          return true;
        }


        if(!visible_count)
        {
            visible_count =   visible_interval;
          invisible_count = invisible_interval;
        }


      return true;
    }


  return false;
}


void
EffectObject::
update() noexcept
{
  Actor::update();

    if(!frozen_flag)
    {
      ++frame_count;
    }


  x_position += x_vector;
  y_position += y_vector;

  set_base_point(Point(*(fixed_t("0.5")+x_position),
                       *(fixed_t("0.5")+y_position)));

    if(controll_callback)
    {
      controll_callback(*this);
    }
}


}




