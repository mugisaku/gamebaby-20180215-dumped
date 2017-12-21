#include"enum_definition.hpp"



namespace ty{
namespace ty_types{


void
enum_definition::
append(std::string_view  name) noexcept
{
  m_enumerator_list.emplace_back(name,m_last_value++);
}


void
enum_definition::
append(std::string_view  name, int  value) noexcept
{
  m_last_value = value;

  append(name);
}


void
enum_definition::
print(FILE*  f) const noexcept
{
    for(auto&  en: m_enumerator_list)
    {
      en.print(f);

      fprintf(f,"\n");
    }
}


}}




