#ifndef game_ScriptElement_HPP
#define game_ScriptElement_HPP


#include"Director.hpp"
#include"Square.hpp"
#include"Piece.hpp"
#include"GameData.hpp"
#include<memory>


namespace gmbb{


enum class
ScriptElementKind
{
  null,
  script,
  text,
  choosing,
  command,
  call_shop,

};


class Script;


struct
ChoosingEntry
{
  std::string  text;

  std::unique_ptr<Script>  script;

  ChoosingEntry(std::string const&  text_, Script*  sc) noexcept:
  text(text_),
  script(sc){}

};


union
ScriptElementData
{
  std::string                   string;
  std::vector<ChoosingEntry>  choosing;
  Script*                       script;

   ScriptElementData(){}
  ~ScriptElementData(){}

};


class
ScriptElement
{
  ScriptElementKind  kind=ScriptElementKind::null;
  ScriptElementData  data;

public:
  ScriptElement() noexcept{}
  ScriptElement(gamn::Value const&  v) noexcept;
  ScriptElement(ScriptElement const&  rhs) noexcept=delete;
  ScriptElement(ScriptElement&&       rhs) noexcept{*this = std::move(rhs);}
 ~ScriptElement(){clear();}

  ScriptElement&  operator=(ScriptElement const&  rhs) noexcept=delete;
  ScriptElement&  operator=(ScriptElement&&       rhs) noexcept;

  void  clear() noexcept;

  void  print() const noexcept;

};


}




#endif




