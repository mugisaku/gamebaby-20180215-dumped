#ifndef game_Board_HPP
#define game_Board_HPP


#include"Director.hpp"
#include"Square.hpp"
#include"Piece.hpp"
#include"GameData.hpp"


namespace gmbb{


class
Board: public Director
{
  Point  view_point;

  std::vector<Piece*>  hunger;

  Square  square_table[board_height][board_width];

  void  link() noexcept;

public:
  Board() noexcept{link();}


  void  clear_all_distance() noexcept;

  covered_ptr<Piece>  new_piece() noexcept;

  void  delete_piece(covered_ptr<Piece>  p) noexcept;


  void  move_view_point(int  x, int  y) noexcept;

  void  set_view_point_by_piece(Piece&  p) noexcept;

  Point  get_view_point() const noexcept{return view_point;}

  Square const*  get_square_begin() const noexcept{return &square_table[             0][          0];}
  Square const*    get_square_end() const noexcept{return &square_table[board_height-1][board_width];}

  Square&        get_square(      int  x, int  y)       noexcept{return square_table[y][x];}
  Square const&  get_const_square(int  x, int  y) const noexcept{return square_table[y][x];}

  void  update() noexcept override;

  void  render(Image&  dst, Point  offset) const noexcept override;

};


}




#endif




