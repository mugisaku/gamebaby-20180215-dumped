#ifndef GMBB_Task_HPP
#define GMBB_Task_HPP


#include"gmbb_Figures.hpp"
#include"gmbb_Image.hpp"
#include"Pointer.hpp"
#include<string>


namespace gmbb{


class GroupTask;


class
Task
{
  std::string  name;

  Point  base_point;

  rw_ptr<GroupTask>  group;

  rw_ptr<Task>  previous;
  rw_ptr<Task>      next;

public:
  Task(         ) noexcept{}
  Task(Point  pt) noexcept: base_point(pt){}

  void                set_name(std::string const&  name_)       noexcept{       name = name_;}
  std::string const&  get_name(                         ) const noexcept{return name        ;}

  void   set_base_point(Point  pt)       noexcept{       base_point = pt;}
  Point  get_base_point(         ) const noexcept{return base_point     ;}

  rw_ptr<Task>  get_previous() const noexcept{return previous;}
  rw_ptr<Task>  get_next()     const noexcept{return next;}

  ro_ptr<Task>  get_ro_previous() const noexcept{return previous.get_ro();}
  ro_ptr<Task>  get_ro_next()     const noexcept{return next.get_ro();}

  void               set_group(GroupTask&  grp)       noexcept{       group = &grp;}
  rw_ptr<GroupTask>  get_group(               ) const noexcept{return group       ;}

  void  connect(Task&  new_next) noexcept;

  void  disconnect() noexcept;

  virtual bool  is_group() const noexcept{return false;}

  virtual void  update() noexcept{}

  virtual void  render(Image&  dst, Point  offset) const noexcept{}

};



}




#endif




