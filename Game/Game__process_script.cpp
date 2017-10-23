#include"Game_private.hpp"


namespace gmbb{


using namespace script;


namespace{


void
process_new_piece(ListNode const*  cur) noexcept
{
  std::string const*  p_name=nullptr;

  TalkData  tkdat;

  int  x = 0;
  int  y = 0;

    while(cur)
    {
      auto&  v = cur->value;

      cur = cur->next;

        if(v.is_string("name"))
        {
          p_name = &v.get_string();
        }

      else
        if(v.is_list("talk"))
        {
          auto&  ls = v.get_list();

          tkdat.target = ls[ValueTag(ValueKind::string,"with")].get_string();

          auto&  content_v = ls[ValueTag(ValueKind::list,"content")];

          auto  current = content_v.get_list().get_first();

            while(current)
            {
              auto&  v = current->value;

              current = current->next;

                if(v == ValueKind::string)
                {
                  tkdat.content += v.get_string();
                  tkdat.content += '\n';
                }
            }
        }

      else
        if(v.is_list("initial_position"))
        {
          auto&  ls = v.get_list();

          x = ls["x"].get_integer();
          y = ls["y"].get_integer();
        }
    }


    if(p_name)
    {
      auto  p = board.new_piece(*p_name,x,y);

        if(p)
        {
          p->set_render_callback(render_hero_piece);

          p->push_talk_data(std::move(tkdat));
        }
    }
}


}


void
process_script(Director&  di, ListNode const*&  cur)
{
    while(cur)
    {
      static std::string const  new_piece_s("new_piece");

      auto&  v = cur->value;

      cur = cur->next;

        if(v.is(ValueKind::list,new_piece_s))
        {
          process_new_piece(v.get_list().get_first());
        }
    }
}




}




