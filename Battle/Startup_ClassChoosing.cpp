#include"Startup.hpp"
#include"SystemData.hpp"
#include"ReadOnlyData.hpp"




namespace gmbb{


namespace{


void
render(Image&  dst, Point  point, int  index)
{
  auto&  plb = ro::player_base_table[index];

  dst.print(plb.get_name().data(),point,sys::glset);
}


ColumnStyleMenuWindow
menu_window(Menu(8*8,16,3,render),1,Point(80,60));


class
Message: public Task
{
public:
  Message(): Task(Point(64,16)){}

  void  render(Image&  dst, Point  offset) const noexcept override
  {
    offset += get_base_point();

    dst.print("しゅじんこうの　クラスを　きめてください",offset,sys::glset);
  }

} message;


class
SpecsWindow: public Window
{
public:
  SpecsWindow(): Window(8*31,16*7,Point(16,128)){}

  void  render(Image&  dst, Point  offset) const noexcept override
  {
    Window::render(dst,offset);

    offset += get_base_point();

    offset.x += 8;
    offset.y += 8;

    StringBuffer  sbuf;

    const int  y_base = offset.y;

    const auto&  pl = tmp::player;

    dst.print(sbuf("たいりょく　　　%2d",pl.get_body_strength()),offset           ,sys::glset);
//    dst.print(sbuf("せいしんりょく　%2d",get_pl.mind_strength()),offset.move_y(16),sys::glset);
    dst.print(sbuf("すばやさ　　　　%2d",pl.get_agility()      ),offset.move_y(16),sys::glset);
    dst.print(sbuf("しゅびりょく　　%2d",pl.get_defense()      ),offset.move_y(16),sys::glset);
//    dst.print(sbuf("ちりょく　　　　%2d",pl.get_intellect()    ),offset.move_y(16),sys::glset);

    offset.x +=   8*12;
    offset.y  = y_base;

    dst.print(sbuf("こうげき　%3d…かいすう　%2d",pl.get_attack_strength(),pl.get_number_of_attacks()),offset           ,sys::glset);
    dst.print(sbuf("ぼうぎょ　%3d…かいすう　%2d",pl.get_guard_strength(),pl.get_number_of_guards())  ,offset.move_y(16),sys::glset);
//    dst.print(sbuf("まほう　　%3d…かいすう　%2d",pl.get_magic_strength(),pl.get_number_of_magics())  ,offset.move_y(16),sys::glset);
  }

} specs_window;


void
step(uint32_t&  pc) noexcept
{
    if(!pc)
    {
      sys::root_task.push(message);
      sys::root_task.push(menu_window);
      sys::root_task.push(specs_window);

      ++pc;
    }


    if(sys::interval_timer.check(120,ctrl.get_time()))
    {
           if(ctrl.is_up_button_pressing()  ){menu_window.move_cursor_to_up()  ;}
      else if(ctrl.is_down_button_pressing()){menu_window.move_cursor_to_down();}

      static_cast<PlayerBase&>(tmp::hero) = ro::player_base_table[menu_window.get_item_index()];

      tmp::player.set_data(tmp::hero);

      tmp::player.update();
    }


    if(ctrl.is_p_button_pressing())
    {
      tmp::player.replenish_hp();
      tmp::player.replenish_mp();

      coprocesses::pop();
    }
}


}


void
terminate_class_choosing() noexcept
{
  sys::root_task.erase(message);
  sys::root_task.erase(menu_window);
  sys::root_task.erase(specs_window);
}


const coprocess
coprocess_of_class_choosing("class_making",step);


}




