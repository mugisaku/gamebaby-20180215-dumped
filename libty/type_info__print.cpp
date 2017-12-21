#include"type_info_PRIVATE.hpp"



namespace ty{
namespace ty_types{


void
type_info::
print(FILE*  f) const noexcept
{
  fprintf(f,"   id %s\n",get_id().data());

    if(is_complete())
    {
      fprintf(f," size %zu\n",get_size());
      fprintf(f,"align %zu\n",get_align());
    }
}


void
type_info::
print_human_readable(FILE*  f) const noexcept
{
    switch(m_data->kind)
    {
  case(type_kind::const_qualified):
      fprintf(f,"const ");

      m_data->definition.ti.print_human_readable(f);
      break;
  case(type_kind::volatile_qualified):
      fprintf(f,"volatile ");

      m_data->definition.ti.print_human_readable(f);
      break;
  case(type_kind::const_volatile_qualified):
      fprintf(f,"const volatile ");

      m_data->definition.ti.print_human_readable(f);
      break;
  case(type_kind::pointer):
      m_data->definition.ti.print_human_readable(f);

      fprintf(f,"*");
      break;
  case(type_kind::reference):
      m_data->definition.ti.print_human_readable(f);

      fprintf(f,"&");
      break;
  case(type_kind::array):
      m_data->definition.ti.print_human_readable(f);

      fprintf(f,"[%zu]",m_data->number_of_elements);
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
      fprintf(f,"int%d",8*m_data->definition.size);
      break;
  case(type_kind::unsigned_integral):
      fprintf(f,"uint%d",8*m_data->definition.size);
      break;
  case(type_kind::struct_):
      fprintf(f,"struct{\n");

        if(m_data->definition.st)
        {
          m_data->definition.st->print(f);
        }

      else
        {
          fprintf(f,"**have no definition**");
        }

      fprintf(f,"\n}\n");
      break;
  case(type_kind::enum_):
      fprintf(f,"enum{\n");

        if(m_data->definition.en)
        {
          m_data->definition.en->print(f);
        }

      else
        {
          fprintf(f,"**have no definition**");
        }


      fprintf(f,"\n}\n");
      break;
  case(type_kind::union_):
      fprintf(f,"union{\n");

        if(m_data->definition.un)
        {
          m_data->definition.un->print(f);
        }

      else
        {
          fprintf(f,"**have no definition**");
        }


      fprintf(f,"\n}\n");
      break;
  case(type_kind::function_pointer):
      m_data->definition.sig.print(f);
      break;
    }
}


}}




