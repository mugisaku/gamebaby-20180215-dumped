#ifndef type_table_HPP
#define type_table_HPP


#include"declaration.hpp"



namespace ty{
namespace types{


template<typename  T>
inline void
add(declaration&&  new_decl, T&  container) noexcept
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
inline const declaration*
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

using types::add;
using types::find_by_name;
using types::print_all_types;


}


#endif




