#include"ty.hpp"


using namespace ty;


type_decl   i8(type_info::make_i8(),"int8_t");
type_decl   u8(type_info::make_u8(),"uint8_t");
type_decl  i16(type_info::make_i16(),"int16_t");
type_decl  u16(type_info::make_u16(),"uint16_t");
type_decl  i32(type_info::make_i32(),"int32_t");
type_decl  u32(type_info::make_u32(),"uint32_t");


int
main(int  argc, char**  argv)
{
  auto  a_td = type_decl(type_info::make_empty_struct(),"struct a");
  auto  b_td = type_decl(type_info::make_empty_struct(),"struct b");

  auto&  a_stdef = a_td.get_info().get_struct_def();

  a_stdef.append(i8,"test");
  a_stdef.append(i16,"test");
  a_stdef.append(i8,"test");
  a_stdef.append(i8,"test");
  a_stdef.append(i32,"test");
  a_stdef.append(i8,"test");
  a_stdef.append(i16,"test");
  a_stdef.append(i8,"test");

  a_stdef.test_align(0);

  a_stdef.print();

  printf("\n");


  auto&  b_stdef = b_td.get_info().get_struct_def();

  b_stdef.append(i8,"test");
  b_stdef.append(a_td,"test");
  b_stdef.append(a_td,"test");
  b_stdef.append(i8,"test");
  b_stdef.append(a_td,"test");
  b_stdef.append(a_td,"test");

  b_stdef.test_align(0);

  b_stdef.print();

  printf("\n");


  type_info::make_i8().add_const().remove_const().add_pointer().add_const().remove_const().add_pointer().print();
  printf("\n");
  type_info::make_i8().add_pointer().add_const().remove_const().add_pointer().add_const().remove_const().print();
  printf("\n");

  return 0;
}




