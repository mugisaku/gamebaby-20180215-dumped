#include"Game_private.hpp"


namespace gmbb{


using namespace script;


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
          auto  p = board.new_piece();

            if(p)
            {
              p->make_from(v.get_list());
            }
        }
    }
}




}




