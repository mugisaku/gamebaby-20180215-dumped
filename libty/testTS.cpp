#include"ty.hpp"


using namespace ty;


int
main(int  argc, char**  argv)
{
  auto  a_ti = type_info::make_u8();
  auto  b_ti = a_ti.add_rvalue_reference().remove_reference();

  a_ti.print();

  printf("\n");

  b_ti.print();

  printf("\n");

  printf("a and b is %ssame\n",(a_ti == b_ti)? "":"not ");

  return 0;
}




