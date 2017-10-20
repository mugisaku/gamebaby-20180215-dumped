#ifndef GMBB_Task_HPP
#define GMBB_Task_HPP


#include"gmbb_Figures.hpp"
#include"gmbb_Image.hpp"
#include"covered_ptr"
#include<string>


namespace gmbb{


class
Task
{
  std::string  name;

  bool  active_flag=false;

  covered_ptr<Task>  previous;
  covered_ptr<Task>      next;

public:
  void                set_name(std::string const&  name_)       noexcept{       name = name_;}
  std::string const&  get_name(                         ) const noexcept{return name        ;}

  covered_ptr<Task>  get_previous() const noexcept{return previous;}
  covered_ptr<Task>  get_next()     const noexcept{return next;}

  Task const*  get_const_previous() const noexcept{return previous.get_const_raw_pointer();}
  Task const*  get_const_next()     const noexcept{return next.get_const_raw_pointer();}

  void    set_active_flag() noexcept{active_flag =  true;}
  void  unset_active_flag() noexcept{active_flag = false;}
  bool   test_active_flag() const noexcept{return active_flag;}

  void  connect(Task&  new_next) noexcept;

  void  disconnect() noexcept;

  virtual void  update() noexcept{}

  virtual void  render(Image&  dst, Point  offset) const noexcept{}

};


class
GraphicalTask: public Task
{
  Point  base_point;

public:
  GraphicalTask(         ) noexcept{}
  GraphicalTask(Point  pt) noexcept: base_point(pt){}

  void   set_base_point(Point  pt) noexcept{base_point = pt;}
  Point  get_base_point() const noexcept{return base_point;}

};



}




#endif




