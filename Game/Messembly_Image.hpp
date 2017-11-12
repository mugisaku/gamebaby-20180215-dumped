#ifndef GMBB_Messanbly_Image_HPP
#define GMBB_Messanbly_Image_HPP


#include"gmbb_Standard.hpp"
#include"gamn.hpp"
#include<cstdio>
#include<cstdint>
#include<string>


namespace      gmbb{
namespace messembly{


enum class
Opcode
{
  nop,//No OPeration
  txt,//TeXT
  cho,//CHOosing
  jmp,//JuMP
  eq ,//EQual
  neq,//Not EQual
  bra,//BRAnch
  xfn,//eXternal FuNction
  sfl,//Set FLag
  ufl,//Unset FLag
  tfl,//Test FLag
  cal,//CALl
  ret,//RETurn

};


struct
Instruction
{
  using code_t = uint32_t;

  code_t  code;

  Instruction(Opcode  op=Opcode::nop, uint32_t  imm=0) noexcept:
  code((static_cast<int>(op)<<24)|(imm&0xFFFFFF)){}

  Opcode  get_opcode() const noexcept{return static_cast<Opcode>(code>>24);}

  uint32_t  get_imm() const noexcept{return code&0xFFFFFF;}

};


struct
Symbol
{
  std::string  name;

  uint32_t  index;

  Symbol():
  index(0){}

  Symbol(const std::string&  name_, uint32_t  i=0):
  name(name_),
  index(i){}

};


struct
Choosing
{
  std::vector<std::string>  entries;

};


class
Image
{
  std::vector<Symbol>  entry_symbol_table;
  std::vector<Symbol>  label_symbol_table;
  std::vector<std::string>   string_table;

  std::vector<Choosing>   choosing_table;

  std::vector<Instruction>  binary;

public:
  Image(std::vector<Symbol>&&  entsym_tbl,
        std::vector<Symbol>&&  lblsym_tbl,
        std::vector<std::string>&&  str_tbl,
        std::vector<Choosing>&&  cho_tbl,
        std::vector<Instruction>&&  bin):
  entry_symbol_table(std::move(entsym_tbl)),
  label_symbol_table(std::move(lblsym_tbl)),
  string_table(std::move(str_tbl)),
  choosing_table(std::move(cho_tbl)),
  binary(std::move(bin)){}


  const Symbol&  get_entry_symbol(uint32_t  i) const noexcept{return entry_symbol_table[i];}
  const Symbol&  get_label_symbol(uint32_t  i) const noexcept{return label_symbol_table[i];}

  const std::string&  get_string(uint32_t  i) const noexcept{return string_table[i];}
  const Choosing&  get_choosing(uint32_t  i) const noexcept{return choosing_table[i];}

  Instruction  get_instruction(uint32_t  i) const noexcept{return binary[i];}

  const Symbol*  find_entry_symbol(const std::string&  name) const noexcept;
  const Symbol*  find_label_symbol(const std::string&  name) const noexcept;

  void  print() const noexcept;

};


}}




#endif




