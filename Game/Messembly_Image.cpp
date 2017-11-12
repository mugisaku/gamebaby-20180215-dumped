#include"Messembly_Image.hpp"




namespace gmbb{
namespace messembly{


const Symbol*
Image::
find_entry_symbol(const std::string&  name) const noexcept
{
    for(auto&  sym: entry_symbol_table)
    {
        if(sym.name == name)
        {
          return &sym;
        }
    }


  return nullptr;
}


const Symbol*
Image::
find_label_symbol(const std::string&  name) const noexcept
{
    for(auto&  sym: label_symbol_table)
    {
        if(sym.name == name)
        {
          return &sym;
        }
    }


  return nullptr;
}


void
Image::
print() const noexcept
{
}




}}




