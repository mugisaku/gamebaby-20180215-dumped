#include"Role.hpp"
#include"Game_private.hpp"




namespace gmbb{


using namespace script;


void
Role::
build_from(List const&  ls) noexcept
{
    for(auto&  v: ls)
    {
/*
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
*/
    }
}


script::ListNode const*
Role::
find_talk_data(std::string const&  target) const noexcept
{
    for(auto&  tka: talk_action_table)
    {
        if(tka.with == target)
        {
          return tka.content;
        }
    }


  return nullptr;
}




}




