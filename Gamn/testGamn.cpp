#include"gmbb_Standard.hpp"
#include"gamn.hpp"


using namespace gamn;


int
main(int  argc, char**  argv)
{
  List  ls;

    try
    {
      ls = List("../script.gamn");
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




