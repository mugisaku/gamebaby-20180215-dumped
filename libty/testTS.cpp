#include"ty.hpp"


using namespace ty;


int
main(int  argc, char**  argv)
{
  struct_def  def;
  struct_def  def2;

  def.append(type_info::make_i8(),"test");
  def.append(type_info::make_i32(),"test");
  def.append(type_info::make_i8(),"test");
  def.append(type_info::make_i8(),"test");
  def.append(type_info::make_i8(),"test");
  def.append(type_info::make_i16(),"test");
  def.append(type_info::make_i8(),"test");
  def.append(type_info::make_i16(),"test");
  def.append(type_info::make_i8(),"test");

  def.print();

  def.test_align(0);

  printf("\n");


  auto  a_ti = type_info::make_user_defined(udef_type_info(std::move(def)));

  def2.append(a_ti,"test");
  def2.append(a_ti,"test");
  def2.append(a_ti,"test");
  def2.append(a_ti,"test");

  def2.print();

  def2.test_align(0);

  printf("\n");

  auto  b_ti = type_info::make_user_defined(udef_type_info(std::move(def2)));

  a_ti.print();

  printf("\n");

  b_ti.print();

  printf("\n");

  printf("a and b is %ssame\n",(a_ti == b_ti)? "":"not ");

  return 0;
}




