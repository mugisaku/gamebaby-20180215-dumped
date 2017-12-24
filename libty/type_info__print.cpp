#include"type_info_PRIVATE.hpp"



namespace ty{
namespace ty_types{


void
type_info::
print_id(FILE*  f) const noexcept
{
  fprintf(f,"%s",get_id().data());
}


void
type_info::
print_size_and_align(FILE*  f) const noexcept
{
  fprintf(f,"(size %zu, align %zu)",get_size(),get_align());
}


void
type_info::
print(FILE*  f) const noexcept
{
    if(is_const())
    {
      fprintf(f,"const ");
    }


    if(is_volatile())
    {
      fprintf(f,"volatile ");
    }


    switch(m_data->m_kind)
    {
  case(type_kind::pointer):
      fprintf(f,"pointer<");

      m_data->m_set.ti.print(f);

      fprintf(f,">");
      break;
  case(type_kind::reference):
      fprintf(f,"reference<");

      m_data->m_set.ti.print(f);

      fprintf(f,">");
      break;
  case(type_kind::rvalue_reference):
      fprintf(f,"rvalue_reference<");

      m_data->m_set.ti.print(f);

      fprintf(f,">>");
      break;
  case(type_kind::boolean):
      fprintf(f,"bool");
      break;
  case(type_kind::null_pointer):
      fprintf(f,"null_pointer");
      break;
  case(type_kind::generic_pointer):
      fprintf(f,"generic_pointer");
      break;
  case(type_kind::integral):
      fprintf(f,"int%d",8*m_data->m_set.size);
      break;
  case(type_kind::unsigned_integral):
      fprintf(f,"uint%d",8*m_data->m_set.size);
      break;
  case(type_kind::function_pointer):
      m_data->m_set.sig.print(f);
      break;
  case(type_kind::array):
      m_data->m_set.arr.print(f);
      break;
  case(type_kind::struct_):
      fprintf(f,"struct");
      break;
  case(type_kind::enum_):
      fprintf(f,"enum");
      break;
  case(type_kind::union_):
      fprintf(f,"union");
      break;
    }
}


}}




