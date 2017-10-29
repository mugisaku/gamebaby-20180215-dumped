#ifndef game_Piece_HPP
#define game_Piece_HPP


#include"gmbb_Standard.hpp"
#include"Hero.hpp"
#include"Enemy.hpp"
#include"Square.hpp"
#include"EffectObject.hpp"
#include"Role.hpp"


namespace gmbb{


enum class
PieceKind
{
  null,
  hero,
  friend_hero,
  enemy,

};


struct
Attribute
{
  static constexpr int    human = 0x001;
  static constexpr int    beast = 0x002;
  static constexpr int   spirit = 0x004;
  static constexpr int    plant = 0x008;
  static constexpr int  machine = 0x010;
  static constexpr int    flyer = 0x020;
  static constexpr int   undead = 0x040;
  static constexpr int   insect = 0x080;
  static constexpr int    shell = 0x100;
  static constexpr int  aquatic = 0x200;
  static constexpr int   dragon = 0x400;

};


class Board;
class Square;


class
Piece: public EffectObject
{
  covered_ptr<Board>  board;

  PieceKind  kind=PieceKind::null;

  covered_ptr<Square>  square;

  Role  role;


  int  hp    ;
  int  hp_max;

  int     sleep_count=0;
  int      seal_count=0;
  int    poison_count=0;
  int   confuse_count=0;
  int     blind_count=0;
  int  illusion_count=0;

  covered_ptr<GameItem>   sword_item;
  covered_ptr<GameItem>  shield_item;
  covered_ptr<GameItem>    belt_item;

public:
  Piece(Board&  brd) noexcept: board(&brd){}
  Piece(Piece const&) noexcept=delete;
  Piece(Piece&&     ) noexcept=delete;


  Piece&  operator=(Piece const&) noexcept=delete;
  Piece&  operator=(Piece&&     ) noexcept=delete;

  void  reset(Hero&   hero) noexcept;
  void  reset(Enemy&  enem) noexcept;


  void                 set_square(covered_ptr<Square>  sq)       noexcept{       square = sq;}
  covered_ptr<Square>  get_square(                       ) const noexcept{return square     ;}

  void  make_from(script::List const&  ls) noexcept;

  Role const&  get_role() const noexcept{return role;}

  int  get_hp()     const noexcept{return hp    ;}
  int  get_hp_max() const noexcept{return hp_max;}

  void    hold_item(covered_ptr<GameItem>  p) noexcept;
  bool  unhold_item(covered_ptr<GameItem>  p) noexcept;

  void  unhold_sword() noexcept;
  void  unhold_shield() noexcept;
  void  unhold_belt() noexcept;

  covered_ptr<GameItem>  get_sword_item()  const noexcept{return  sword_item;}
  covered_ptr<GameItem>  get_shield_item() const noexcept{return shield_item;}
  covered_ptr<GameItem>  get_belt_item()   const noexcept{return   belt_item;}

  void  set_controll_callback(ControllCallback<Piece>  cb) noexcept
  {controll_callback = reinterpret_cast<ControllCallback<EffectObject>>(cb);}

  void  set_render_callback(RenderCallback<Piece>  cb) noexcept
  {render_callback = reinterpret_cast<RenderCallback<EffectObject>>(cb);}


  Board&  get_board() const noexcept{return *board;}

  void  set_position_by_current_square() noexcept;

};




}




#endif




