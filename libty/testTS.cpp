#include"ty.hpp"




int
main(int  argc, char**  argv)
{
  using namespace ty;

  struct_declaration  decl("test");

  auto  def = std::make_unique<struct_definition>();

  def->append(type_info::make_i8(),"test");
  def->append(type_info::make_i16(),"test");
  def->append(type_info::make_i8(),"test");
  def->append(type_info::make_i8(),"test");
  def->append(type_info::make_i8(),"test");
  def->append(type_info::make_i32(),"test");
  def->append(type_info::make_i8(),"test");
  def->append(type_info::make_i16(),"test");
  def->append(type_info::make_i8(),"test");
  def->append(type_info::make_i8(),"test");
  def->append(type_info::make_i8(),"test");
  def->append(type_info::make_i16(),"test");
  def->append(type_info::make_i8(),"test");

  def->finalize();

  decl.set_definition(std::move(def));

  auto  a_ti = type_info::make_struct(decl);

  auto  b_ti = a_ti.remove_extent();

  a_ti.print_human_readable();

  printf("\n");

  b_ti.print_human_readable();

  printf("\n");

  printf("a and b is %ssame\n",(a_ti == b_ti)? "":"not ");


  return 0;
}




