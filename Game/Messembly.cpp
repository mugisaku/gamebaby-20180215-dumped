#include"Messembly.hpp"




namespace gmbb{
namespace messembly{




void
Machine::
step() noexcept
{
    if(slept || halted)
    {
      return;
    }


  auto  instr = image->get_instruction(pc++);

  opcode = instr.get_opcode();

    switch(opcode)
    {
  case(Opcode::nop):
      break;
  case(Opcode::sfl):
        {
          auto  name = image->get_string(instr.get_imm()).data();

          environment::set_value(name,"1");
        }
      break;
  case(Opcode::ufl):
        {
          auto  name = image->get_string(instr.get_imm()).data();

          environment::set_value(name,"0");
        }
      break;
  case(Opcode::tfl):
        {
          auto  name = image->get_string(instr.get_imm()).data();

          auto&  v = environment::get_value(name);

          boolean = (v.size() && (v[0] != '0'));
        }
      break;
  case(Opcode::ttx):
  case(Opcode::adb):
  case(Opcode::xfn):
        if(process_cb)
        {
          process_cb(*this,image->get_string(instr.get_imm()));
        }
      break;
  case(Opcode::jmp):
      pc = instr.get_imm();
      break;
  case(Opcode::bra):
        if(boolean)
        {
          pc = instr.get_imm();
        }
      break;
  case(Opcode::eq):
      boolean = (chosen_value == instr.get_imm());
      break;
  case(Opcode::neq):
      boolean = (chosen_value != instr.get_imm());
      break;
  case(Opcode::xch):
        if(process_cb)
        {
          static const std::string  dummy_s("CHOOSING");

          slept = true;

          process_cb(*this,dummy_s);
        }
      break;
  case(Opcode::cal):
      call_stack.emplace_back(pc)                 ;
                              pc = instr.get_imm();
      break;
  case(Opcode::ret):
        if(call_stack.size())
        {
          pc = call_stack.back();

          call_stack.pop_back();
        }

      else
        {
          halted = true;
        }
      break;
  default:;
      printf("[messembly vm error]");
    }
}




void
Machine::
set_chosen_value(uint32_t  v) noexcept
{
  chosen_value =     v;
  slept        = false;
}


bool
Machine::
reset(const Image&  img, const char*  entry_name) noexcept
{
  image = &img;

  auto  sym = img.find_entry_symbol(entry_name);

    if(!sym)
    {
      printf("[messembly error] エントリー%sが見つからない",entry_name);

      halted = true;

      return false;
    }


  pc = sym->index;

   slept = false;
  halted = false;

  call_stack.clear();

  return true;
}


}}




