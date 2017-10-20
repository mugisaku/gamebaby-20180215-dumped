#include"Game_private.hpp"


namespace gmbb{


using namespace script;


namespace{


class
Reader
{
  Token const*&  cur;

  std::string const*    name;
  TokenString const*  string;

public:
  Reader(Token const*&  cur_) noexcept: cur(cur_){}

  bool  operator()() noexcept
  {
      if(cur)
      {
          if((cur[0] == TokenKind::identifier) &&
             (cur[1] == TokenKind::token_string))
          {
            name   = &cur++->get_string();
            string = &cur++->get_token_string();

            return true;
          }
      }


    cur = nullptr;

    return false;
  }


  bool  operator==(char const*  s) const noexcept{return *name == s;}

  Token const*  operator*() const noexcept{return string->data();}

};


void
process_new_piece(Reader  r) noexcept
{
  std::string const*  p_name=nullptr;

  int  x = 0;
  int  y = 0;

    while(r())
    {
        if(r == "name")
        {
          p_name = &(*r)[0].get_string();
        }

      else
        if(r == "type")
        {
        }

      else
        if(r == "initial_position")
        {
          x = (*r)[0].get_integer();
          y = (*r)[1].get_integer();
        }
    }


    if(p_name)
    {
      auto  p = board.new_piece(*p_name,x,y);

        if(p)
        {
          p->set_render_callback(render_hero_piece);
        }
    }
}


}


void
process_script(Director&  di, script::Token const*&  cur)
{
  Reader  r(cur);

    while(r())
    {
      auto  p = *r;

        if(r == "new_piece")
        {
          process_new_piece(Reader(p));
        }
    }
}




}




