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

    switch(instr.get_opcode())
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

          boolean = environment::get_value(name)[0] == '1';
        }
      break;
  case(Opcode::txt):
        if(text_transfer)
        {
          text_transfer(image->get_string(instr.get_imm()));
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
  case(Opcode::cho):
        if(choosing_callback)
        {
          auto&  choosing = image->get_choosing(instr.get_imm());

          slept = true;

          choosing_callback(*this,choosing);
        }
      break;
  case(Opcode::xfn):
        if(external_function)
        {
          boolean = external_function(image->get_string(instr.get_imm()));
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


void
Machine::
reset(const Image*  img, const char*  entry_name) noexcept
{
  image = img;

    if(img)
    {
      auto  sym = img->find_entry_symbol(entry_name);

        if(!sym)
        {
          printf("[messembly error] エントリー%sが見つからない",entry_name);
        }


      pc = sym? sym->index:0;
    }


   slept = false;
  halted = false;

  call_stack.clear();
}


}}




