#include"ScriptManager.hpp"
#include"ShopManager.hpp"
#include<vector>
#include<cstring>


namespace gmbb{


using namespace script;


namespace{


std::vector<List*>
list_table;


using Table = std::vector<Value const*>;


Table  routines;
Table     roles;
Table  messages;


void
push(Value const&  v, Table&  tbl)
{
    if(v == ValueKind::list)
    {
        for(auto&  v: v.get_list())
        {
          tbl.emplace_back(&v);
        }
    }

  else
    if(v == ValueKind::value)
    {
      tbl.emplace_back(&v.get_value());
    }
}


void
push(Value const&  v)
{
       if(v == "routine"){push(v,routines);}
  else if(v == "message"){push(v,messages);}
  else if(v == "role"){push(v,roles);}
  else if(v.is_list("shop"))
    {
        for(auto&  vv: v.get_list())
        {
            if(vv.is_list())
            {
              push_shop(*new Shop(vv.get_name(),vv.get_list()));
            }
        }
    }
}


Value const*
find(Table&  tbl, char const*  value_name) noexcept
{
  auto const  len = std::strlen(value_name);

    for(auto&  ptr: tbl)
    {
      auto&  name = ptr->get_name();

        if((name.size() == len) && (std::strcmp(name.data(),value_name) == 0))
        {
          return ptr;
        }
    }


  return nullptr;
}


}


script::Value const*  find_message_script(char const*  value_name) noexcept{find(messages,value_name);}
script::Value const*  find_routine_script(char const*  value_name) noexcept{find(routines,value_name);}
script::Value const*  find_role_script(char const*  value_name) noexcept{find(roles,value_name);}



void
load_script_file(char const*  filepath) noexcept
{
  auto  s = make_string_from_file(filepath);

  StreamReader  r(s.data());

  List*  ls;

    try
    {
      ls = new List(r);
    }


    catch(StreamError const&  err)
    {
      err.print();

      return;
    }


    if(ls)
    {
      list_table.emplace_back(ls);

        for(auto&  v: *ls)
        {
          push(v);
        }
    }
}


}




