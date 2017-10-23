#ifndef GMBB_Actor_HPP
#define GMBB_Actor_HPP


#include"gmbb_Standard.hpp"
#include"covered_ptr"
#include<cstdio>
#include<string>


namespace gmbb{


class Director;
class Actor;


struct
Action
{
  int  counter;

  Action(int  c=1): counter(c){}

  virtual void  operator()() noexcept{}

};


class
Actor: public Task
{
  std::vector<Action*>  action_stack;

  covered_ptr<Director>  director;

public:
  Actor() noexcept{}

  void  update() noexcept override;

  virtual void  print() const noexcept{printf("%s(%p)",get_name().data(),this);}

};


}




#endif




