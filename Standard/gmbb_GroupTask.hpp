#ifndef GMBB_GroupTask_HPP
#define GMBB_GroupTask_HPP


#include"gmbb_Task.hpp"


namespace gmbb{




class
GroupTask: public Task
{
  rw_ptr<Task>  first;
  rw_ptr<Task>   last;

  uint32_t  number=0;

public:
  void  push_to_first(Task&  t) noexcept;
  void   push_to_last(Task&  t) noexcept;
  void   push(Task&  t) noexcept{push_to_last(t);}

  void  erase( Task&  t) noexcept;

  uint32_t  get_number_of_tasks() const noexcept{return number;}

  rw_ptr<Task>  get_first() const noexcept{return first;}
  rw_ptr<Task>   get_last() const noexcept{return  last;}

  ro_ptr<Task>  get_ro_first() const noexcept{return first.get_ro();}
  ro_ptr<Task>   get_ro_last() const noexcept{return  last.get_ro();}

  void  update() noexcept override;

  void  render(Image&  dst, Point  offset) const noexcept override;

  rw_ptr<Task>  find_by_name(std::string const&  name_) const noexcept;

  bool  is_group() const noexcept override{return true;}

  void  print() noexcept;

};


}




#endif




