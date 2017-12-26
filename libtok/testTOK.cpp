#include"tok.hpp"


using namespace tok;


int
main(int  argc, char**  argv)
{
    if(argc != 2)
    {
      return 0;
    }


  token_list  ls;

    try
    {
      ls = make_token_list_from_file(argv[1]);
    }


    catch(const token_info&  ti)
    {
      printf("\n");

      return -1;
    }


    for(auto&  tok: ls)
    {
      tok.print();

      printf("\n");
    }


  return 0;
}




