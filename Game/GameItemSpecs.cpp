#include"GameItemSpecs.hpp"


namespace gmbb{




GameItemSpecs::
GameItemSpecs(char const*  name_, Price  pri, char const*  desc, SwordSpecs const&  swd) noexcept:
name(name_),
price(pri),
description(desc),
kind(GameItemKind::sword)
{data.sword = swd;}


GameItemSpecs::
GameItemSpecs(char const*  name_, Price  pri, char const*  desc, ShieldSpecs const&  shl) noexcept:
name(name_),
price(pri),
description(desc),
kind(GameItemKind::shield)
{data.shield = shl;}


GameItemSpecs::
GameItemSpecs(char const*  name_, Price  pri, char const*  desc, BeltSpecs const&  blt) noexcept:
name(name_),
price(pri),
description(desc),
kind(GameItemKind::belt)
{data.belt = blt;}


GameItemSpecs::
GameItemSpecs(char const*  name_, Price  pri, char const*  desc, WandSpecs const&  wnd) noexcept:
name(name_),
price(pri),
description(desc),
kind(GameItemKind::wand)
{data.wand = wnd;}


GameItemSpecs::
GameItemSpecs(char const*  name_, Price  pri, char const*  desc, CardSpecs const&  crd) noexcept:
name(name_),
price(pri),
description(desc),
kind(GameItemKind::card)
{data.card = crd;}


GameItemSpecs::
GameItemSpecs(char const*  name_, Price  pri, char const*  desc, WaterSpecs const&  wat) noexcept:
name(name_),
price(pri),
description(desc),
kind(GameItemKind::water)
{data.water = wat;}




char const*
GameItemSpecs::
get_first_operation_name() const noexcept
{
    if((kind == GameItemKind::sword ) ||
       (kind == GameItemKind::shield) ||
       (kind == GameItemKind::belt  ))
    {
      return "そうび";
    }

  else
    if(kind == GameItemKind::wand)
    {
      return "ふる";
    }

  else
    if(kind == GameItemKind::card)
    {
      return "となえる";
    }

  else
    if(kind == GameItemKind::water)
    {
      return "あびる";
    }


  return nullptr;
}



std::pair<GameItemSpecs const*,size_t>
GameItemSpecs::
get() noexcept
{
    static GameItemSpecs const  table[] =
    {
      GameItemSpecs("どうのつるぎ",Price(0),"",SwordSpecs(0)),
      GameItemSpecs("てつのつるぎ"    ,Price(0),"",SwordSpecs(0)),
      GameItemSpecs("はがねのつるぎ"  ,Price(0),"",SwordSpecs(0)),
      GameItemSpecs("きのたて",Price(0),"",ShieldSpecs(0)),
      GameItemSpecs("かわのたて",Price(0),"",ShieldSpecs(0)),
      GameItemSpecs("てつのたて",Price(0),"",ShieldSpecs(0)),
      GameItemSpecs("やすいおび",Price(0),"",BeltSpecs()),
      GameItemSpecs("ふつうのおび",Price(0),"",BeltSpecs()),
      GameItemSpecs("こうきゅうおび",Price(0),"",BeltSpecs()),
      GameItemSpecs("ふこうのおび",Price(0),"",BeltSpecs()),
      GameItemSpecs("ねむりのつえ",Price(0),"",WandSpecs()),
      GameItemSpecs("どくのつえ",Price(0),"",WandSpecs()),
      GameItemSpecs("ちからのふだ",Price(0),"",CardSpecs()),
      GameItemSpecs("まもりのふだ",Price(0),"",CardSpecs()),
      GameItemSpecs("だっしゅつのふだ",Price(0),"",CardSpecs()),
      GameItemSpecs("いやしのみず",Price(0),"",WaterSpecs()),
      GameItemSpecs("どくのみず",Price(0),"",WaterSpecs()),
      GameItemSpecs("ただのみず",Price(0),"",WaterSpecs()),
      GameItemSpecs("くさいのみず",Price(0),"",WaterSpecs()),
      GameItemSpecs("きせきのみず",Price(0),"",WaterSpecs()),
    };


  return std::make_pair<GameItemSpecs const*,size_t>(table,sizeof(table)/sizeof(*table));
};


GameItemSpecs const*
GameItemSpecs::
find_by_name(std::string const&  name) noexcept
{
}


}




