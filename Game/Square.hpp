#ifndef game_Square_HPP
#define game_Square_HPP


#include"gmbb_Standard.hpp"
#include"Sack.hpp"
#include"Trap.hpp"




namespace gmbb{


using distance_t = uint32_t;


class Square;
class Piece;


enum class
SquareKind
{
  null,
  wall,
  room,
};


class
SquareLinkSet
{
  covered_ptr<Square>  table[8];

public:
  void                 set(Direction  d, covered_ptr<Square>  sq)       noexcept{       table[static_cast<int>(d)] = sq;}
  covered_ptr<Square>  get(Direction  d                         ) const noexcept{return table[static_cast<int>(d)]     ;}

};


class
Square
{
  int  x;
  int  y;

  covered_ptr<Piece>  piece_ptr;

  distance_t  distance=0;

  int  mpp_value;//mpp is MultiPurPose

  SquareKind  kind=SquareKind::null;

  SquareLinkSet  linkset;

  GameItem  item;

  Trap  trap;

public:
  bool  operator==(SquareKind  k) const noexcept{return kind == k;}
  bool  operator!=(SquareKind  k) const noexcept{return kind != k;}

  int  get_x() const noexcept{return x;}
  int  get_y() const noexcept{return y;}


  void  remove_piece() noexcept;

  covered_ptr<Piece>  get_piece(                     ) const noexcept{return piece_ptr    ;}
  void                set_piece(covered_ptr<Piece>  p)       noexcept{       piece_ptr = p;}

  void  set_mpp_value(int  v)       noexcept{       mpp_value = v;}
  int   get_mpp_value(      ) const noexcept{return mpp_value    ;}

  void         set_distance(distance_t  d)       noexcept{       distance = d;}
  distance_t   get_distance(             ) const noexcept{return distance    ;}


  SquareKind  get_kind(             ) const noexcept{return kind    ;}
  void        set_kind(SquareKind  k)       noexcept{       kind = k;}


  void  reset(int  x_, int  y_, SquareLinkSet&  lnset) noexcept;

  SquareLinkSet&  get_linkset() noexcept{return linkset;}

  covered_ptr<Square>         operator[](Direction  d) const noexcept{return linkset.get(d);}
  covered_ptr<Square>  get_linked_square(Direction  d) const noexcept{return linkset.get(d);}


  void                 set_item(GameItem const&  i               ) noexcept{item = i;}
  covered_ptr<Square>  put_item(GameItem const&  i, distance_t  d) noexcept;

  GameItem&        get_item()       noexcept{return item;}
  GameItem const&  get_item() const noexcept{return item;}

  bool  can_put_item() const noexcept{return (kind == SquareKind::room) && !item && !trap;}

  void         set_trap(Trap const&  tr)       noexcept{       trap = tr;}
  Trap const&  get_trap(               ) const noexcept{return trap     ;}

};


}




#endif




