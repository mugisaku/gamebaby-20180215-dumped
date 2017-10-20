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

  script::Token const*  current=nullptr;

};


class
Director: public Task
{
  using ScriptProcessor = void(*)(Director&  di, script::Token const*&  cur);

  covered_ptr<Board>  board;

  covered_ptr<Actor>  first;
  covered_ptr<Actor>   last;

  uint32_t  number_of_actors=0;

  script::Token const*  script_current=nullptr;

  ScriptProcessor  script_processor=nullptr;

  std::list<Context>  context_table;

public:
  Director() noexcept{}
  Director(Board&  brd) noexcept: board(&brd){}

  void  set_script(script::Token const*  tok) noexcept{script_current = tok;}

  void  set_script_processor(ScriptProcessor  scproc) noexcept{script_processor = scproc;}

  void  insert_to_first(Actor&  target) noexcept;
  void  insert_to_last( Actor&  target) noexcept;

  void  remove(Actor&  target) noexcept;

  uint32_t  get_number_of_actors() const noexcept{return number_of_actors;}

  covered_ptr<Actor>  get_first() const noexcept{return first;}
  covered_ptr<Actor>  get_last()  const noexcept{return  last;}

  Actor const*  get_const_first() const noexcept{return first.get_const_raw_pointer();}
  Actor const*  get_const_last()  const noexcept{return  last.get_const_raw_pointer();}

  void  update() noexcept override;

  void  render(Image&  dst, Point  offset) const noexcept override;

  template<typename  T>
  void
  for_each(T&  t) const noexcept
  {
    auto  next = first;

      while(next)
      {
        t(*next);

        next = next->get_next();
      }
  }


  covered_ptr<Actor>  find_by_name(std::string const&  name_) const noexcept;

  void  print() const noexcept;

};


}




#endif




