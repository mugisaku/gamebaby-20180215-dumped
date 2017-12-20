#include"type_table.hpp"




int
main(int  argc, char**  argv)
{
  using namespace ts;

  auto  ti = type_info::make_i8();

  ti.add_pointer().print();

  return 0;
}




