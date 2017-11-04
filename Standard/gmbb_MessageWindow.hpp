#ifndef GMBB_MessageWindow_HPP_INCLUDED
#define GMBB_MessageWindow_HPP_INCLUDED


#include"gmbb_Figures.hpp"
#include"gmbb_Window.hpp"
#include"gmbb_Text.hpp"




namespace gmbb{


class
MessageWindow: public Window
{
  static constexpr size_t  buffer_size = 1024;

  Text  text;

  GlyphSet const*  glyphset;

  char  buffer[buffer_size+1];

  char*         input_pointer;
  char const*  output_pointer;

  ColorIndex  coloring[4];

  char const*  get_buffer_tail() const noexcept{return buffer+buffer_size;}

public:
  MessageWindow(GlyphSet&  glset, int  column_number, int  row_number, Point  pt) noexcept;

  void  clear() noexcept;
  void  reset() noexcept;

  bool  is_stopped()   const noexcept{return text.is_full();}
  bool  is_remaining() const noexcept{return(output_pointer < input_pointer);}
  bool  is_clean() const noexcept{return(input_pointer == buffer);}

  void  step();
  void  scroll();

  void  push(char const*  s, bool  with_newline=true);
  void  push(std::initializer_list<char const*>  ls);

  void  render(Image&  dst, Point  offset) const noexcept override;

};


}




#endif




