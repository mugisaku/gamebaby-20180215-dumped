#include"Game/Messembly_ImageBuilder.hpp"
#include"gamn.hpp"



using namespace gmbb::messembly;
using namespace gamn;


int
main(int  argc, char**  argv)
{
  ImageBuilder  builder;


  gmbb::Stream  s;

  s.set_content_from_file("../script.gamn");

  gamn::StreamReader  r(s.get_content().data());

  gamn::List*  ls;

    try
    {
      ls = new List(r);
    }


    catch(StreamError const&  err)
    {
      err.print();

      return 0;
    }


    if(ls)
    {
        for(auto&  v: *ls)
        {
            if(v.is_list("message"))
            {
              builder.push_entry_list(v.get_list());
            }
        }
    }


  builder.finalize();
  builder.print();

  auto  img = builder.build();

  img.print();

  return 0;
}




