#ifndef type_table_HPP
#define type_table_HPP


#include"variable_declaration.hpp"



namespace ty{
namespace ty_types{


template<typename  T>
inline void
add(variable_declaration&&  new_decl, T&  container) noexcept
{
    for(auto&  decl: container)
    {
        if(decl.get_name() == new_decl.get_name())
        {
          return;
        }
    }


  container.emplace_back(std::move(new_decl));
}


template<typename  T>
inline const variable_declaration*
find_by_name(const T&  container, std::string_view  name) noexcept
{
    for(auto&  decl: container)
    {
        if(decl.get_name() == name)
        {
          return &decl;
        }
    }


  return nullptr;
}


template<typename  T>
inline void
print_all_types(const T&  container, FILE*  f) noexcept
{
  fprintf(f,"{\n");

    for(auto&  decl: container)
    {
      decl.print(f);

      fprintf(f,"\n");
    }


  fprintf(f,"}\n\n");
}


}

using ty_types::add;
using ty_types::find_by_name;
using ty_types::print_all_types;


}


#endif




