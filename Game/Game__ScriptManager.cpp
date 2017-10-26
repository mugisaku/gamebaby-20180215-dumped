#include"Game_private.hpp"
#include<vector>


namespace gmbb{


using namespace script;


namespace{


std::vector<List*>
list_table;


struct
Directory
{
  std::string  type_name;

  std::vector<Value const*>  value_table;

  Directory(std::string const&  name) noexcept: type_name(name){}

};


std::vector<Directory>
directories;


void
push(Value const&  v, Directory&  d)
{
    if(v == ValueKind::list)
    {
      auto  cur = v.get_list().get_first();

        while(cur)
        {
          d.value_table.emplace_back(&cur->value);

          cur = cur->next;
        }
    }

  else
    if(v == ValueKind::value)
    {
      d.value_table.emplace_back(&v.get_value());
    }
}


void
push(Value const&  v)
{
    for(auto&  d: directories)
    {
        if(d.type_name == v.get_name())
        {
          push(v,d);

          return;
        }
    }


  directories.emplace_back(v.get_name());

  push(v,directories.back());
}


}


Value const*
find_gson(std::string const&  type_name, std::string const&  value_name) noexcept
{
/*
    for(auto&  d: directories)
    {
printf("%s...",d.type_name.data());

    for(auto&  v: d.value_table)
    {
v->print();
printf("\n");
    }
    }
*/


    for(auto&  d: directories)
    {
        if(d.type_name == type_name)
        {
            for(auto  v: d.value_table)
            {
                if(*v == value_name)
                {
                  return v;
                }
            }


          return nullptr;
        }
    }


  return nullptr;
}


void
open_script(char const*  filepath) noexcept
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

      auto  current = ls->get_first();

        while(current)
        {
          push(current->value);

          current = current->next;
        }
    }
}


}




