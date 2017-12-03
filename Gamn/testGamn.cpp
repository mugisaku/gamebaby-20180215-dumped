#include"gmbb_Standard.hpp"
#include"gamn.hpp"


using namespace gamn;


int
main(int  argc, char**  argv)
{
    if(argc != 2)
    {
      return 0;
    }


  List  ls;

    try
    {
      ls = List(argv[1]);
    }


    catch(StreamError const&  err)
    {
      err.print();

      printf("\n");

      return -1;
    }

    catch(...)
    {
      printf("...\n");

      return -1;
    }


  ls.print();


  return 0;
}




