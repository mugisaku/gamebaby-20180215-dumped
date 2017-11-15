#include"Game_private.hpp"


namespace gmbb{


namespace{
void
skip_spaces(const char*&  p) noexcept
{
    for(;;)
    {
      auto  c = *p;

        if((c !=  ' ') &&
           (c != '\t') &&
           (c != '\r') &&
           (c != '\n'))
        {
          break;
        }


      ++p;
    }
}


bool
test(char  c) noexcept
{
  return(((c >= '0') && (c <= '9')) ||
         ((c >= 'a') && (c <= 'z')) ||
         ((c >= 'A') && (c <= 'Z')) ||
         ((c == '_')              ));
}


std::vector<std::string>
scan(const std::string&  src) noexcept
{
  auto  p = src.data();

  std::vector<std::string>  ss;

    for(;;)
    {
      skip_spaces(p);

        if(test(*p))
        {
          std::string  s;

            while(test(*p))
            {
              s += *p++;
            }


          ss.emplace_back(std::move(s));
        }

      else
        {
          break;
        }
    }


  return std::move(ss);
}


}


void
close_game(const Controller&  ctrl) noexcept
{
  static int  n = 7;

  static uint32_t  last;

  constexpr uint32_t  interval = 200;

    if(n)
    {
        if(ctrl.get_time() >= (last+interval))
        {
          screen::enable_add_color();

          last = ctrl.get_time();

          screen::set_add_r(screen::get_add_r()-1);
          screen::set_add_g(screen::get_add_g()-1);
          screen::set_add_b(screen::get_add_b()-1);

          --n;
        }
    }
}


void
process_string(messembly::Machine&  m, const std::string&  s) noexcept
{
  auto  ss = scan(s);

    if(ss.size() == 1)
    {
      auto&  s0 = ss[0];

           if(s0 == "exit"){m.halt();}
      else if(s0 == "close_game"){push_routine(close_game);}
    }

  else
    if(ss.size() == 2)
    {
      auto&  s0 = ss[0];
      auto&  s1 = ss[1];

        if(s0 == "shop")
        {
          start_shopping(s1.data(),nullptr);
        }
    }
}


}




