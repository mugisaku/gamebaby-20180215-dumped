#ifndef GMBB_grouptask_HPP
#define GMBB_grouptask_HPP


#include"libgbstd/task.hpp"


namespace gbstd{
namespace tasks{




class
group_task: public task
{
  rw_ptr<task>  m_first;
  rw_ptr<task>   m_last;

  uint32_t  m_number_of_tasks=0;

public:
  void  push_to_first(task&  t) noexcept;
  void   push_to_last(task&  t) noexcept;
  void   push(task&  t) noexcept{push_to_last(t);}

  void  erase(task&  t) noexcept;

  uint32_t  get_number_of_tasks() const noexcept{return m_number_of_tasks;}

  rw_ptr<task>  get_first() const noexcept{return m_first;}
  rw_ptr<task>   get_last() const noexcept{return  m_last;}

  ro_ptr<task>  get_ro_first() const noexcept{return m_first.get_ro();}
  ro_ptr<task>   get_ro_last() const noexcept{return  m_last.get_ro();}

  void  update() noexcept override;

  void  render(image&  dst, point  offset) const noexcept override;

  rw_ptr<task>  find_by_name(std::string_view  name) const noexcept;

  bool  is_group() const noexcept override{return true;}

  void  print() noexcept;

};


}


using tasks::group_task;


}




#endif




