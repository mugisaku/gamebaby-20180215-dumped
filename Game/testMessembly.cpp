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


  Machine  m;

  m.reset(&img,"when_has_happiness_powder");

  m.set_text_transfer([](const std::string&  s_){
    printf("%s\n",s_.data());
  });

  m.set_choosing_callback([](Machine&  m, const Choosing&  cho){
    int  n = 1;

      for(auto&  ent: cho.entries)
      {
        printf("  %2d <%s>\n",n++,ent.data());
      }


    printf("[input a number you want]\n");

    char  buf[256];

    fgets(buf,sizeof(buf),stdin);

      while(sscanf(buf,"%d",&n) != 1)
      {
        fgets(buf,sizeof(buf),stdin);
      }


    m.set_chosen_value(n? n-1:0);
  });

    while(!m.is_halted())
    {
      m.step();
    }


  return 0;
}




