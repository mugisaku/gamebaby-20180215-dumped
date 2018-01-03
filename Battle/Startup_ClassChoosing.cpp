#include"Startup.hpp"
#include"SystemData.hpp"
#include"ReadOnlyData.hpp"




namespace{


void
render(gbstd::image&  dst, gbstd::point  point, int  index)
{
  auto&  plb = ro::player_base_table[index];

  dst.print(plb.get_name().data(),point,sys::font);
}




gbstd::column_menu
  menu_window(gbstd::menu_base(gbstd::menu_item_renderer(8*8,16,render),3),
  1,gbstd::point(80,60)
);


class
Message: public gbstd::task
{
public:
  Message(): task(gbstd::point(64,16)){}

  void  render(gbstd::image&  dst, gbstd::point  offset) const noexcept override
  {
    offset += get_base_point();

    dst.print("しゅじんこうの　クラスを　きめてください",offset,sys::font);
  }

} message;


class
SpecsWindow: public gbstd::window
{
public:
  SpecsWindow(): window(8*31,16*7,gbstd::point(16,128)){}

  void  render(gbstd::image&  dst, gbstd::point  offset) const noexcept override
  {
    window::render(dst,offset);

    offset += get_base_point();

    offset.x += 8;
    offset.y += 8;

    const int  y_base = offset.y;

    const auto&  pl = tmp::player;

    dst.print(gbstd::make_text("たいりょく　　　%2d",pl.get_body_strength()),offset           ,sys::font);
//    dst.print(gbstd::make_text("せいしんりょく　%2d",get_pl.mind_strength()),offset.move_y(16),sys::font);
    dst.print(gbstd::make_text("すばやさ　　　　%2d",pl.get_agility()      ),offset.move_y(16),sys::font);
    dst.print(gbstd::make_text("しゅびりょく　　%2d",pl.get_defense()      ),offset.move_y(16),sys::font);
//    dst.print(gbstd::make_text("ちりょく　　　　%2d",pl.get_intellect()    ),offset.move_y(16),sys::font);

    offset.x +=   8*12;
    offset.y  = y_base;

    dst.print(gbstd::make_text("こうげき　%3d…かいすう　%2d",pl.get_attack_strength(),pl.get_number_of_attacks()),offset           ,sys::font);
    dst.print(gbstd::make_text("ぼうぎょ　%3d…かいすう　%2d",pl.get_guard_strength(),pl.get_number_of_guards())  ,offset.move_y(16),sys::font);
//    dst.print(gbstd::make_text("まほう　　%3d…かいすう　%2d",pl.get_magic_strength(),pl.get_number_of_magics())  ,offset.move_y(16),sys::font);
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


    if(sys::interval_timer.check(120,gbstd::ctrl.get_time()))
    {
           if(gbstd::ctrl.is_up_button_pressing()  ){menu_window.move_cursor_to_up()  ;}
      else if(gbstd::ctrl.is_down_button_pressing()){menu_window.move_cursor_to_down();}

      static_cast<PlayerBase&>(tmp::hero) = ro::player_base_table[menu_window.get_item_index()];

      tmp::player.set_data(tmp::hero);

      tmp::player.update();
    }


    if(gbstd::ctrl.is_p_button_pressing())
    {
      tmp::player.replenish_hp();
      tmp::player.replenish_mp();

      gbstd::playworks::pop();
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


const gbstd::playwork
playwork_of_class_choosing("class_making",step);




