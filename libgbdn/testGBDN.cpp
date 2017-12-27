#include"gbdn.hpp"


using namespace gbdn;


int
main(int  argc, char**  argv)
{
    if(argc != 2)
    {
      return 0;
    }


  list  ls;

    try
    {
      ls = list(argv[1]);
    }


    catch(const tok::stream_context&  ctx)
    {
      ctx.print();

      printf("\n");

      return -1;
    }


  ls.print();

  printf("\n");

  auto  v = ls.access({"class"});

    if(v)
    {
      v->print();

      printf("\n");
    }


  return 0;
}




