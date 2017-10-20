#include"Game_private.hpp"


namespace gmbb{


namespace{


class
StatusReportor: public Window
{
public:
  StatusReportor(): Window(300,80,Point(8,160)){}

  void  render(Image&  dst, Point  offset) const noexcept override;

} *rep;


void
StatusReportor::
render(gmbb::Image&  dst, Point  offset) const noexcept
{
  Window::render(dst,offset);

  char  buf[256];

  Point  pt = get_base_point()+offset;

  auto  w = glset.get_width();
  auto  h = glset.get_height();

  pt.x += 8;
  pt.y += 8;

  auto   sword = hero_piece->get_sword_item();
  auto  shield = hero_piece->get_shield_item();
  auto    belt = hero_piece->get_belt_item();

  dst.print(u"けん",pt,glset);

    if(sword)
    {
      dst.print((*sword)->get_name(),pt+Point(w*3),glset);
    }


  pt.y += h;

  dst.print(u"たて",pt,glset);

    if(shield)
    {
      dst.print((*shield)->get_name(),pt+Point(w*3),glset);
    }


  pt.y += h;

  dst.print(u"おび",pt,glset);

    if(belt)
    {
      dst.print((*belt)->get_name(),pt+Point(w*3),glset);
    }


  pt.y += h;


}


}


void
show_status_reportor() noexcept
{
    if(!rep)
    {
      rep = new StatusReportor;

      rep->set_name("status repoter");
    }


  task_list::push(*rep);

  rep->set_state(WindowState::full_opened);
}


void
hide_status_reportor() noexcept
{
  task_list::erase(*rep);
}


}




