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

  m.reset(img,"when_has_happiness_powder");

  m.set_process_callback([](Machine&  m, const std::string&  txt){
    static int  n;

    char  buf[256];

    int  res;

      switch(m.get_opcode())
      {
    case(Opcode::ttx):
        printf("%s\n",txt.data());
        break;
    case(Opcode::adb):
        printf("  %2d <%s>\n",++n,txt.data());
        break;
    case(Opcode::xch):
        printf("[input a number you want]\n");

        n = 0;

        fgets(buf,sizeof(buf),stdin);

          while(sscanf(buf,"%d",&res) != 1)
          {
            fgets(buf,sizeof(buf),stdin);
          }


        m.set_chosen_value(res-1);
        break;
    case(Opcode::xfn):
        break;
      }
  });


    while(!m.is_halted())
    {
      m.step();
    }


  return 0;
}




