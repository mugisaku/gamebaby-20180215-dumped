#include"Startup.hpp"
#include"SystemData.hpp"
#include"ReadOnlyData.hpp"




namespace gmbb{


namespace{


FixedString
label("class choosing");


void
render(Image&  dst, Point  point, int  index)
{
  auto&  plb = ro::player_base_table[index];

  dst.print(plb.name.data(),point,system_data::glset);
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

    dst.print("しゅじんこうの　クラスを　きめてください",offset,system_data::glset);
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

    dst.print(sbuf("たいりょく　　　%2d",pl.body_strength),offset           ,system_data::glset);
//    dst.print(sbuf("せいしんりょく　%2d",pl.mind_strength),offset.move_y(16),system_data::glset);
    dst.print(sbuf("すばやさ　　　　%2d",pl.agility      ),offset.move_y(16),system_data::glset);
    dst.print(sbuf("しゅびりょく　　%2d",pl.defense      ),offset.move_y(16),system_data::glset);
//    dst.print(sbuf("ちりょく　　　　%2d",pl.intellect    ),offset.move_y(16),system_data::glset);

    offset.x +=   8*12;
    offset.y  = y_base;

    dst.print(sbuf("こうげき　%3d…かいすう　%2d",pl.attack_strength,pl.number_of_attacks),offset           ,system_data::glset);
    dst.print(sbuf("ぼうぎょ　%3d…かいすう　%2d",pl.guard_strength,pl.number_of_guards)  ,offset.move_y(16),system_data::glset);
//    dst.print(sbuf("まほう　　%3d…かいすう　%2d",pl.magic_strength,pl.number_of_magics)  ,offset.move_y(16),system_data::glset);
  }

} specs_window;


void
step(Controller const&  ctrl) noexcept
{
    if(system_data::interval_timer.check(120,ctrl.get_time()))
    {
           if(ctrl.is_up_button_pressing()  ){menu_window.move_cursor_to_up()  ;}
      else if(ctrl.is_down_button_pressing()){menu_window.move_cursor_to_down();}

      static_cast<PlayerBase&>(tmp::hero) = ro::player_base_table[menu_window.get_item_index()];

      tmp::player = Player(tmp::hero);

      tmp::player.update();
    }


    if(ctrl.is_p_button_pressing())
    {
      tmp::player.replenish_hp();
      tmp::player.replenish_mp();

      pop_routine(label.pointer);
    }
}


}


void
terminate_class_choosing() noexcept
{
  system_data::root_task.erase(message);
  system_data::root_task.erase(menu_window);
  system_data::root_task.erase(specs_window);
}


void
start_class_choosing(coreturn_t  ret) noexcept
{
  system_data::root_task.push(message);
  system_data::root_task.push(menu_window);
  system_data::root_task.push(specs_window);

  push_routine(label.pointer,step,ret);
}


}




