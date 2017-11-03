#ifndef game_Script_HPP
#define game_Script_HPP


#include"ScriptElement.hpp"


namespace gmbb{


class
Script
{
  ScriptElement*  table;

  int  number=0;

public:
  Script(script::List const&  ls) noexcept;
 ~Script(){clear();}

  void  clear() noexcept;

  int  size() const noexcept{return number;}

  ScriptElement const*  begin() const noexcept{return table;}
  ScriptElement const*    end() const noexcept{return table+number;}

  void  print() const noexcept;

};


}




#endif




