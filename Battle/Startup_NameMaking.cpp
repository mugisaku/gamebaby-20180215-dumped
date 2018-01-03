#include"Startup.hpp"
#include"SystemData.hpp"




namespace{


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


gbstd::point
cursor;


class
KanaWindow: public  gbstd::window
{
public:
  KanaWindow(): window(16+(8*23),16*6,gbstd::point(32,120)){};

  void  render(gbstd::image&  dst, gbstd::point  offset) const noexcept override
  {
    window::render(dst,offset);

    offset += get_base_point();

    offset.x += 8;
    offset.y += 8;

    auto  p = current;

    gbstd::point  pt;

      for(int  n = 0;  n < 5;  ++n)
      {
        dst.print(*p++,offset+pt,sys::font);

        pt.y += 16;
      }


    offset.x +=  8*cursor.x;
    offset.y += 16*cursor.y+4;

    dst.print(u'_',offset,sys::font);
  }

} character_window;


class
NameWindow: public  gbstd::window
{
public:
  NameWindow(): window(16+(8*length_max),16*2,gbstd::point(120,80)){};

  void  render(gbstd::image&  dst, gbstd::point  offset) const noexcept override
  {
    window::render(dst,offset);

    offset += get_base_point();

    offset.x += 8;
    offset.y += 8;

    dst.print(tmp::name_buffer.get_data(),offset,sys::font);

      if(tmp::name_buffer.get_length() < length_max)
      {
        offset.x += 8*tmp::name_buffer.get_length();

        dst.print(u'■',offset,sys::font);
      }
  }

} name_window;


class
Message: public gbstd::task
{
public:
  bool  too_short=false;

  Message(): task(gbstd::point(64,16)){}

  void  render(gbstd::image&  dst, gbstd::point  offset) const noexcept override
  {
    offset += get_base_point();

    dst.print("しゅじんこうの　なまえを　きめてください",offset,sys::font);

      if(too_short)
      {
        dst.print("なまえが　みじかすぎます",offset.move_x(16).move_y(16),sys::font);
      }
  }

} message;


char16_t
get() noexcept
{
  return current[cursor.y][cursor.x];
}


void
step(uint32_t&  pc) noexcept
{
    if(!pc)
    {
      cursor = gbstd::point(10,0);

      message.too_short = false;

      sys::root_task.push(character_window);
      sys::root_task.push(     name_window);
      sys::root_task.push(         message);

      ++pc;
    }


  static bool  lock;

    if(sys::interval_timer.check(120,gbstd::ctrl.get_time()))
    {
           if(gbstd::ctrl.is_up_button_pressing()   && (cursor.y    )){--cursor.y;}
      else if(gbstd::ctrl.is_down_button_pressing() && (cursor.y < 4)){++cursor.y;}

           if(gbstd::ctrl.is_left_button_pressing()  && (cursor.x     )){--cursor.x;}
      else if(gbstd::ctrl.is_right_button_pressing() && (cursor.x < 23)){++cursor.x;}
    }


    if(gbstd::ctrl.is_p_button_pressing())
    {
      message.too_short = false;

        if(!lock && (tmp::name_buffer.get_length() < length_max))
        {
          tmp::name_buffer.push(get());
        }


      lock = true;
    }

  else
    if(gbstd::ctrl.is_n_button_pressing())
    {
        if(!lock && tmp::name_buffer.get_length())
        {
          tmp::name_buffer.pop();
        }


      lock = true;
    }

  else
    if(gbstd::ctrl.is_shift_button_pressing())
    {
        if(!lock)
        {
          current = (current == hiragana_table)? katakana_table
                                               : hiragana_table;
        }


      lock = true;
    }

  else
    if(gbstd::ctrl.is_start_button_pressing())
    {
        if(tmp::name_buffer.get_length() <= 1)
        {
          message.too_short = true;
        }

      else
        if(tmp::name_buffer.get_length() > 1)
        {
          gbstd::playworks::pop();
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


const gbstd::playwork
playwork_of_name_making("name making",step);




