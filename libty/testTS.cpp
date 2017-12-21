#include"type_info.hpp"
#include"struct_definition.hpp"




int
main(int  argc, char**  argv)
{
  using namespace ty;

  struct_declaration  stdecl;

  auto  a_ti = type_info::make_struct(stdecl).make_array(104);

  auto  b_ti = a_ti.remove_extent();

  a_ti.print_human_readable();

  printf("\n");

  b_ti.print_human_readable();

  printf("\n");

  printf("a and b is %ssame\n",(a_ti == b_ti)? "":"not ");


  return 0;
}




