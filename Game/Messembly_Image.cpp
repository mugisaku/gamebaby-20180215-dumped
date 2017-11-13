#include"Messembly_Image.hpp"




namespace gmbb{
namespace messembly{


const Symbol*
Image::
find_entry_symbol(const std::string&  name) const noexcept
{
    for(auto&  sym: entry_symbol_table)
    {
        if(sym.name == name)
        {
          return &sym;
        }
    }


  return nullptr;
}


const Symbol*
Image::
find_label_symbol(const std::string&  name) const noexcept
{
    for(auto&  sym: label_symbol_table)
    {
        if(sym.name == name)
        {
          return &sym;
        }
    }


  return nullptr;
}


void
Image::
print() const noexcept
{
  uint32_t  i = 0;

    for(auto&  instr: binary)
    {
      printf("  %4d ",i++);

      auto  imm = instr.get_imm();

        switch(instr.get_opcode())
        {
      case(Opcode::nop): printf("nop");break;
      case(Opcode::sfl): printf("sfl \"%s\"",string_table[imm].data());break;
      case(Opcode::ufl): printf("ufl \"%s\"",string_table[imm].data());break;
      case(Opcode::tfl): printf("tfl \"%s\"",string_table[imm].data());break;
      case(Opcode::ttx): printf("ttx \"%s\"",string_table[imm].data());break;
      case(Opcode::adb): printf("adb \"%s\"",string_table[imm].data());break;
      case(Opcode::eq ): printf("eq  %4d",imm);break;
      case(Opcode::neq): printf("neq %4d",imm);break;
      case(Opcode::jmp): printf("jmp %4d",imm);break;
      case(Opcode::bra): printf("bra %4d",imm);break;
      case(Opcode::xch): printf("xch");break;
      case(Opcode::xfn): printf("xfn %s",string_table[imm].data());break;
      case(Opcode::cal): printf("cal %4d",imm);break;
      case(Opcode::ret): printf("ret");break;
        }


      printf("\n");
    }
}




}}




