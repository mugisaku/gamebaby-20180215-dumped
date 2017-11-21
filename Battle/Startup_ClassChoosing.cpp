#include"Startup.hpp"
#include"SystemData.hpp"
#include"EmbeddedData.hpp"




namespace gmbb{


namespace{


FixedString
label("class choosing");


const ClassData
classes[] =
{
  {ClassID::warrior,    "せんし",16,4,20,4},
  {ClassID::hunter ,"かりゅうど",80,1, 8,2},
  {ClassID:: thief ,  "とうぞく", 8,8,10,5},
};


void
render(Image&  dst, Point  point, int  index)
{
  auto&  cl = classes[index];

  dst.print(cl.name,point,system_data::glset);
}


ColumnStyleMenuWindow
menu_window(Menu(8*8,16,(sizeof(classes)/sizeof(*classes)),render),1,Point(40,60));


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
  SpecsWindow(): Window(8*13,16*5,Point(120,60)){}

  void  render(Image&  dst, Point  offset) const noexcept override
  {
    Window::render(dst,offset);

    offset += get_base_point();

    offset.x += 8;
    offset.y += 8;

    StringBuffer  sbuf;

    auto&  cl = classes[menu_window.get_item_index()];

    dst.print(sbuf("こうげきりょく　　%2d",cl.strength_of_attack),offset           ,system_data::glset);
    dst.print(sbuf("こうげきかいすう　%2d",cl.number_of_attacks) ,offset.move_y(16),system_data::glset);
    dst.print(sbuf("ぼうぎょりょく　　%2d",cl.strength_of_guard) ,offset.move_y(16),system_data::glset);
    dst.print(sbuf("ぼうぎょかいすう　%2d",cl.number_of_guards)  ,offset.move_y(16),system_data::glset);
  }

} specs_window;


void
step(Controller const&  ctrl) noexcept
{
    if(system_data::interval_timer.check(120,ctrl.get_time()))
    {
           if(ctrl.is_up_button_pressing()  ){menu_window.move_cursor_to_up()  ;}
      else if(ctrl.is_down_button_pressing()){menu_window.move_cursor_to_down();}
    }


    if(ctrl.is_p_button_pressing())
    {
      tmp::character_data.class_data = classes[menu_window.get_item_index()];

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




