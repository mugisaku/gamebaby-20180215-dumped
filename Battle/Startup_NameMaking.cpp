#include"Startup.hpp"
#include"SystemData.hpp"




namespace gmbb{


namespace{


FixedString
label("name making");


const char16_t* const
hiragana_table[] =
{
  u"あいうえお　はひふへほ　がぎぐげご　ぁぃぅぇぉ",
  u"かきくけこ　まみむめも　ざじずぜぞ　ゃ　ゅ　ょ",
  u"さしすせそ　や　ゆ　よ　だぢづでど　っー・　　",
  u"たちつてと　らりるれろ　ばびぶべぼ　　　　　　",
  u"なにぬねの　わをん　　　ぱぴぷぺぽ　　　　　　",

};


const char16_t* const
katakana_table[] =
{
  u"アイウエオ　ハヒフヘホ　ガギグゲゴ　ァィゥェォ",
  u"カキクケコ　マミムメモ　ザジズゼゾ　ャ　ュ　ョ",
  u"サシスセソ　ヤ　ユ　ヨ　ダヂヅデド　ッー・　　",
  u"タチツテト　ラリルレロ　バビブベボ　　　　　　",
  u"ナニヌネノ　ワヲン　　　パピプぺポ　　　　　　",

};


const char16_t* const*
current = hiragana_table;


constexpr int  length_max = 6;


Point
cursor;


class
KanaWindow: public  Window
{
public:
  KanaWindow(): Window(16+(8*23),16*6,Point(32,120)){};

  void  render(Image&  dst, Point  offset) const noexcept override
  {
    Window::render(dst,offset);

    offset += get_base_point();

    offset.x += 8;
    offset.y += 8;

    auto  p = current;

    Point  pt;

      for(int  n = 0;  n < 5;  ++n)
      {
        dst.print(*p++,offset+pt,sys::glset);

        pt.y += 16;
      }


    offset.x +=  8*cursor.x;
    offset.y += 16*cursor.y+4;

    dst.print(u'_',offset,sys::glset);
  }

} character_window;


class
NameWindow: public  Window
{
public:
  NameWindow(): Window(16+(8*length_max),16*2,Point(120,80)){};

  void  render(Image&  dst, Point  offset) const noexcept override
  {
    Window::render(dst,offset);

    offset += get_base_point();

    offset.x += 8;
    offset.y += 8;

    dst.print(tmp::name_buffer.get_data(),offset,sys::glset);

      if(tmp::name_buffer.get_length() < length_max)
      {
        offset.x += 8*tmp::name_buffer.get_length();

        dst.print(u'■',offset,sys::glset);
      }
  }

} name_window;


class
Message: public Task
{
public:
  bool  too_short=false;

  Message(): Task(Point(64,16)){}

  void  render(Image&  dst, Point  offset) const noexcept override
  {
    offset += get_base_point();

    dst.print("しゅじんこうの　なまえを　きめてください",offset,sys::glset);

      if(too_short)
      {
        dst.print("なまえが　みじかすぎます",offset.move_x(16).move_y(16),sys::glset);
      }
  }

} message;


char16_t
get() noexcept
{
  return current[cursor.y][cursor.x];
}


void
step(Controller const&  ctrl) noexcept
{
  static bool  lock;

    if(sys::interval_timer.check(120,ctrl.get_time()))
    {
           if(ctrl.is_up_button_pressing()   && (cursor.y    )){--cursor.y;}
      else if(ctrl.is_down_button_pressing() && (cursor.y < 4)){++cursor.y;}

           if(ctrl.is_left_button_pressing()  && (cursor.x     )){--cursor.x;}
      else if(ctrl.is_right_button_pressing() && (cursor.x < 23)){++cursor.x;}
    }


    if(ctrl.is_p_button_pressing())
    {
      message.too_short = false;

        if(!lock && (tmp::name_buffer.get_length() < length_max))
        {
          tmp::name_buffer.push(get());
        }


      lock = true;
    }

  else
    if(ctrl.is_n_button_pressing())
    {
        if(!lock && tmp::name_buffer.get_length())
        {
          tmp::name_buffer.pop();
        }


      lock = true;
    }

  else
    if(ctrl.is_shift_button_pressing())
    {
        if(!lock)
        {
          current = (current == hiragana_table)? katakana_table
                                               : hiragana_table;
        }


      lock = true;
    }

  else
    if(ctrl.is_start_button_pressing())
    {
        if(tmp::name_buffer.get_length() <= 1)
        {
          message.too_short = true;
        }

      else
        if(tmp::name_buffer.get_length() > 1)
        {
          pop_routine(label.pointer);
        }
    }

  else
    {
      lock = false;
    }
}


}


void
terminate_name_making() noexcept
{
  sys::root_task.erase(character_window);
  sys::root_task.erase(     name_window);
  sys::root_task.erase(         message);
}


void
start_name_making(coreturn_t  ret) noexcept
{
  cursor = Point(10,0);

  message.too_short = false;

  sys::root_task.push(character_window);
  sys::root_task.push(     name_window);
  sys::root_task.push(         message);

  push_routine(label.pointer,step,ret);
}


}




