#include"Game_private.hpp"


namespace gmbb{


namespace{


class
StatusMonitor: public Task
{
public:
  StatusMonitor(): Task(Point(120,0)){}

  void  render(Image&  dst, Point  offset) const noexcept;

} *mon;


void
StatusMonitor::
render(gmbb::Image&  dst, Point  offset) const noexcept
{
  char  buf[256];

  snprintf(buf,sizeof(buf),"HP%3d/%3d",hero_piece->get_hp(),hero_piece->get_hp_max());

  dst.print(buf,get_base_point()+offset,glset);
}


}


void
show_status_monitor() noexcept
{
    if(!mon)
    {
      mon = new StatusMonitor;

      mon->set_name("status monitor");
    }


  root_task.push(*mon);
}


void
hide_status_monitor() noexcept
{
  root_task.erase(*mon);
}



}




