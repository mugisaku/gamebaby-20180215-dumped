#include"type_table.hpp"




int
main(int  argc, char**  argv)
{
  using namespace ts;

  name_type_info(s8_ti.add_pointer(),"s8*");

  print_all_types();

  return 0;
}




