#include"ty.hpp"


using namespace ty;


int
main(int  argc, char**  argv)
{
  struct_definition  def;

  def.append(type_info::make_i8(),"test");

  def.append(type_info::make_i16(),"test");
  def.append(type_info::make_i8(),"test");
  def.append(type_info::make_i8(),"test");
  def.append(type_info::make_i8(),"test");
  def.append(type_info::make_i32(),"test");
  def.append(type_info::make_i8(),"test");
  def.append(type_info::make_i16(),"test");
  def.append(type_info::make_i8(),"test");
  def.append(type_info::make_i8(),"test");
  def.append(type_info::make_i8(),"test");
  def.append(type_info::make_i16(),"test");
  def.append(type_info::make_i8(),"test");


  auto  a_ti = type_info::make_user_defined(user_defined_type_declaration(std::move(def)));

  auto  b_ti = a_ti.add_const();

  a_ti.print_human_readable();

  printf("\n");

  b_ti.print_human_readable();

  printf("\n");

  printf("a and b is %ssame\n",(a_ti == b_ti)? "":"not ");

  return 0;
}




