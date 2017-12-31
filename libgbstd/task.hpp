#ifndef GMBB_task_HPP
#define GMBB_task_HPP


#include"image.hpp"
#include"rw_ptr.hpp"
#include"ro_ptr.hpp"
#include<string>


namespace gbstd{
namespace tasks{


class group_task;


class
task
{
  std::string  m_name;

  point  m_base_point;

  rw_ptr<group_task>  m_group;

  rw_ptr<task>  m_previous;
  rw_ptr<task>      m_next;

public:
  task(         ) noexcept{}
  task(point  pt) noexcept: m_base_point(pt){}

  void                set_name(std::string_view  name)       noexcept{       m_name = name;}
  std::string const&  get_name(                      ) const noexcept{return m_name       ;}

  void   set_base_point(point  pt)       noexcept{       m_base_point = pt;}
  point  get_base_point(         ) const noexcept{return m_base_point     ;}

  rw_ptr<task>  get_previous() const noexcept{return m_previous;}
  rw_ptr<task>  get_next()     const noexcept{return m_next;}

  ro_ptr<task>  get_ro_previous() const noexcept{return m_previous.get_ro();}
  ro_ptr<task>  get_ro_next()     const noexcept{return m_next.get_ro();}

  void                set_group(group_task&  grp)       noexcept{       m_group = &grp;}
  rw_ptr<group_task>  get_group(                ) const noexcept{return m_group       ;}

  void  connect(task&  new_next) noexcept;

  void  disconnect() noexcept;

  virtual bool  is_group() const noexcept{return false;}

  virtual void  update() noexcept{}

  virtual void  render(image&  dst, point  offset) const noexcept{}

};


}


using tasks::task;


}




#endif




