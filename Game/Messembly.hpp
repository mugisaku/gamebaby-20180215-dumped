#ifndef GMBB_Messanbly_HPP
#define GMBB_Messanbly_HPP


#include"Messembly_Image.hpp"


namespace      gmbb{
namespace messembly{


class Machine;


using ProcessCallback = void  (*)(Machine&  m, const std::string&  text);


class
Machine
{
  uint32_t  pc;

  Opcode  opcode;

  bool  boolean;

  uint32_t  chosen_value;

  bool   slept=false;
  bool  halted=false;

  std::vector<uint32_t>  call_stack;

  ProcessCallback  process_cb=nullptr;

  const Image*  image=nullptr;

public:
  void  set_process_callback(ProcessCallback  cb){process_cb = cb;}

  bool   is_slept() const noexcept{return  slept;}
  bool  is_halted() const noexcept{return halted;}

  Opcode  get_opcode() const noexcept{return opcode;}

  uint32_t  get_pc(           ) const noexcept{return pc    ;}
  void      set_pc(uint32_t  v)       noexcept{       pc = v;}

  void  set_chosen_value(uint32_t  v) noexcept;

  bool  reset(const Image&  img, const char*  entry_name) noexcept;

  void  step() noexcept;

};



}}




#endif




