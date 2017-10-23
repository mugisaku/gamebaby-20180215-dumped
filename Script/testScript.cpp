#include"gmbb_Standard.hpp"
#include"gmbb_Script.hpp"


using namespace gmbb::script;


int
main(int  argc, char**  argv)
{
  List  ls;

    try
    {
      ls = List("../script.sc");
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




