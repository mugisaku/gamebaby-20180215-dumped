#ifndef GMBB_Messanbly_HPP
#define GMBB_Messanbly_HPP


#include"Messembly_Image.hpp"


namespace      gmbb{
namespace messembly{


class
Machine
{
  uint32_t  pc;

  bool  boolean;

  uint32_t  chosen_value;

  bool   slept=false;
  bool  halted=false;

  std::vector<uint32_t>  call_stack;

  bool  (*xfunction)(const std::string&  name);

  const Image*  image;

  MessageWindow*  window;

public:
  bool  is_slept() const noexcept{return slept;}
  bool  is_halted() const noexcept{return halted;}

  uint32_t  get_pc(           ) const noexcept{return pc    ;}
  void      set_pc(uint32_t  v)       noexcept{       pc = v;}

  void  set_chosen_value(uint32_t  v) noexcept;

  void  reset(const Image*  img, const char*  entry_name) noexcept;

  void  step() noexcept;

};



}}




#endif




