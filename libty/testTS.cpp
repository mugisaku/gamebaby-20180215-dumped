#include"ty.hpp"


using namespace ty;


int
main(int  argc, char**  argv)
{
  auto  a_ti = type_info::make_empty_struct();
  auto  b_ti = type_info::make_empty_struct();

  auto&  a_stdef = a_ti.get_struct_def();

  a_stdef.append(type_info::make_i8(),"test");
  a_stdef.append(type_info::make_i16(),"test");
  a_stdef.append(type_info::make_i8(),"test");
  a_stdef.append(type_info::make_i8(),"test");
  a_stdef.append(type_info::make_i32(),"test");
  a_stdef.append(type_info::make_i8(),"test");
  a_stdef.append(type_info::make_i16(),"test");
  a_stdef.append(type_info::make_i8(),"test");

  a_stdef.test_align(0);

  a_stdef.print();

  printf("\n");


  auto&  b_stdef = b_ti.get_struct_def();

  b_stdef.append(type_info::make_i8(),"test");
  b_stdef.append(a_ti,"test");
  b_stdef.append(a_ti,"test");
  b_stdef.append(type_info::make_i8(),"test");
  b_stdef.append(a_ti,"test");
  b_stdef.append(a_ti,"test");

  b_stdef.test_align(0);

  b_stdef.print();

  printf("\n");


  type_info::make_i8().add_const().remove_const().add_pointer().add_const().remove_const().add_pointer().print();
  printf("\n");
  type_info::make_i8().add_pointer().add_const().remove_const().add_pointer().add_const().remove_const().print();
  printf("\n");

  return 0;
}




