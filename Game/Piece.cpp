#include"Piece.hpp"
#include"Square.hpp"
#include"Board.hpp"
#include"Game_private.hpp"




namespace gmbb{




void
Piece::
reset(Hero&  hero) noexcept
{
  set_name(hero.get_name());

  hp     = 20;
  hp_max = 20;
}


void
Piece::
reset(Enemy&  enem) noexcept
{
}




void
Piece::
make_from(gamn::List const&  ls) noexcept
{
  auto  cur = ls.get_first();

    while(cur)
    {
      auto&  v = cur->value;

      cur = cur->next;

        if(v.is_string("name"))
        {
          set_name(v.get_string());

            if(get_name() == "hero")
            {
              hero_piece = this;
            }
        }

      else
        if(v == "role")
        {
            if(v.is_list())
            {
              role.build_from(v.get_list());
            }

          else
            if(v.is_string())
            {
              auto  vv = find_role_script(v.get_string().data());

                if(vv)
                {
                  role.build_from(vv->get_list());
                }
            }
        }

      else
        if(v.is_list("initial_position"))
        {
          auto&  ls = v.get_list();

          auto  x = ls["x"].get_integer();
          auto  y = ls["y"].get_integer();

          auto&  sq = board->get_square(x,y);

            if(!sq.get_piece())
            {
              set_square(&sq);

              sq.set_piece(this);

              set_position_by_current_square();
            }          
        }
    }


  set_render_callback(render_hero_piece);

    if(hero_piece == this)
    {
      board->set_view_point_by_piece(*this);

      set_controll_callback(controll_hero_piece);
    }
}




void
Piece::
hold_item(covered_ptr<GameItem>  p) noexcept
{
    if(p)
    {
        if(unhold_item(p))
        {
          return;
        }


      auto&  item = *p;

        switch(item->get_kind())
        {
      case(GameItemKind::sword):
          unhold_sword();

                       p->set_flag(GameItemFlag::equipped);
          sword_item = p                                  ;
          break;
      case(GameItemKind::shield):
          unhold_shield();

                        p->set_flag(GameItemFlag::equipped);
          shield_item = p                                  ;
          break;
      case(GameItemKind::belt):
          unhold_belt();

                      p->set_flag(GameItemFlag::equipped);
          belt_item = p                                 ;
          break;
      default:;
        }


//printf("+%s を装備した\n",gmbb::to_string((*p)->get_name()).data());
    }
}


bool
Piece::
unhold_item(covered_ptr<GameItem>  p) noexcept
{
  bool  res = false;

       if( sword_item == p){ unhold_sword();  res = true;}
  else if(shield_item == p){unhold_shield();  res = true;}
  else if(  belt_item == p){  unhold_belt();  res = true;}


  return res;
}


namespace{
void
unhold(covered_ptr<GameItem>&  p) noexcept
{
    if(p)
    {
//printf("-%s を外した\n",gmbb::to_string((*p)->get_name()).data());
      p->unset_flag(GameItemFlag::equipped);

      p = nullptr;
    }
}
}


void  Piece::unhold_sword()  noexcept{unhold( sword_item);}
void  Piece::unhold_shield() noexcept{unhold(shield_item);}
void  Piece::unhold_belt()   noexcept{unhold(  belt_item);}


void
Piece::
set_position_by_current_square() noexcept
{
  set_x_position(fixed_t(square_size*square->get_x()));
  set_y_position(fixed_t(square_size*square->get_y()));
}


}




