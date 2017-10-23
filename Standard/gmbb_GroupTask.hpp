#ifndef GMBB_GroupTask_HPP
#define GMBB_GroupTask_HPP


#include"gmbb_Task.hpp"


namespace gmbb{




class
GroupTask: public Task
{
  covered_ptr<Task>  first;
  covered_ptr<Task>   last;

  uint32_t  number=0;

public:
  void  push_to_first(Task&  t) noexcept;
  void   push_to_last(Task&  t) noexcept;
  void   push(Task&  t) noexcept{push_to_last(t);}

  void  erase( Task&  t) noexcept;

  uint32_t  get_number_of_tasks() const noexcept{return number;}

  covered_ptr<Task>  get_first() const noexcept{return first;}
  covered_ptr<Task>   get_last() const noexcept{return  last;}

  Task const*  get_const_first() const noexcept{return first.get_const_raw_pointer();}
  Task const*   get_const_last() const noexcept{return  last.get_const_raw_pointer();}

  void  update() noexcept override;

  void  render(Image&  dst, Point  offset) const noexcept override;

  covered_ptr<Task>  find_by_name(std::string const&  name_) const noexcept;

  bool  is_group() const noexcept override{return true;}

  void  print() noexcept;

};


}




#endif




