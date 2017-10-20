#ifndef GMBB_MessageWindow_HPP_INCLUDED
#define GMBB_MessageWindow_HPP_INCLUDED


#include"gmbb_Figures.hpp"
#include"gmbb_Window.hpp"
#include"gmbb_Text.hpp"




namespace gmbb{


class
MessageWindow: public Window
{
  Text  text;

  GlyphSet const*  glyphset;

  char16_t  buffer[1024];

  char16_t const*  output_pointer;
  char16_t*         input_pointer;

  ColorIndex  coloring[4];

public:
  MessageWindow(GlyphSet&  glset, int  column_number, int  row_number, Point  pt) noexcept;

  void  clear() noexcept;
  void  reset() noexcept;

  bool  is_stopped()   const noexcept{return text.is_full();}
  bool  is_remaining() const noexcept{return(output_pointer < input_pointer);}
  bool  is_clean() const noexcept{return(input_pointer == buffer);}

  void  step();
  void  scroll();

  void  push(char const*  s);
  void  push(std::initializer_list<char const*>  ls);

  void  render(Image&  dst, Point  offset) const noexcept override;

};


}




#endif




