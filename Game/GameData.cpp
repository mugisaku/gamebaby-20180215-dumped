#include"GameData.hpp"




namespace gmbb{


Image
character_image;


Rectangle
get_rectangle_for_item(GameItem const&  itm) noexcept
{
  int  x =     0;
  int  y = 24*10;

    switch(itm->get_kind())
    {
  case(GameItemKind::sword):
      break;
  case(GameItemKind::shield):
      y += 24;
      break;
  case(GameItemKind::belt):
      x += 24;
      break;
  case(GameItemKind::wand):
      x += 24;
      y += 24;
      break;
  case(GameItemKind::card):
      x += 24*2;
      break;
  case(GameItemKind::water):
      x += 24*2;
      y += 24;
      break;
    }


  return Rectangle(x,y,square_size,square_size);
}


PickUpParameter
pickup_parameter;


}




