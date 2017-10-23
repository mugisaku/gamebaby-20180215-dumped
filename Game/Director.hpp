#ifndef GMBB_Director_HPP
#define GMBB_Director_HPP


#include"gmbb_Standard.hpp"
#include"gmbb_Script.hpp"
#include"Actor.hpp"
#include<list>


namespace gmbb{


class Board;


struct
Context
{
  covered_ptr<Actor>  target;

  script::ListNode const*  current=nullptr;

};


class
Director: public GroupTask
{
  using ScriptProcessor = void(*)(Director&  di, script::ListNode const*&  cur);

  script::ListNode const*  script_current=nullptr;

  ScriptProcessor  script_processor=nullptr;

  std::list<Context>  context_table;

public:
  void  set_script(script::ListNode const*  nd) noexcept{script_current = nd;}

  void  set_script_processor(ScriptProcessor  scproc) noexcept{script_processor = scproc;}

  void  update() noexcept override;

  void  print() const noexcept;

};


}




#endif




