#include"type_info_PRIVATE.hpp"
#include<new>



namespace ty{
namespace ty_types{




type_info::
type_info(type_kind  kind, std::string_view  id, size_t  size) noexcept:
m_data(new data)
{
  m_data->reference_count = 1;

  m_data->kind = kind;

  m_data->id = id;

  m_data->definition.size = size;
}


type_info::
type_info(type_kind  kind, std::string_view  id, const type_info&  source, size_t  number_of_elements) noexcept:
m_data(new data)
{
  m_data->reference_count = 1;

  m_data->kind = kind;
  m_data->id = id;

  m_data->number_of_elements = number_of_elements;

  new(&m_data->definition) type_info(source);
}


type_info::
type_info(const struct_declaration&  st) noexcept:
m_data(new data)
{
  m_data->reference_count = 1;

  m_data->kind = type_kind::struct_;
  m_data->id = "st";

  m_data->definition.st = &st;
}


type_info::
type_info(const enum_declaration&  en) noexcept:
m_data(new data)
{
  m_data->reference_count = 1;

  m_data->kind = type_kind::enum_;
  m_data->id = "en";

  m_data->definition.en = &en;
}


type_info::
type_info(const union_declaration&  un) noexcept:
m_data(new data)
{
  m_data->reference_count = 1;

  m_data->kind = type_kind::union_;
  m_data->id = "un";

  m_data->definition.un = &un;
}


type_info::
type_info(signature&&  sig) noexcept:
m_data(new data)
{
  m_data->reference_count = 1;

  m_data->kind = type_kind::function_pointer;
  m_data->id = "fp";

  new(&m_data->definition.sig) signature(std::move(sig));
}




type_info&
type_info::
operator=(const type_info&  rhs) noexcept
{
  unrefer();

  m_data = rhs.m_data;

  ++m_data->reference_count;

  return *this;
}


type_info&
type_info::
operator=(type_info&&  rhs) noexcept
{
  unrefer();

  m_data = rhs.m_data          ;
           rhs.m_data = nullptr;

  return *this;
}




void
type_info::
unrefer() noexcept
{
    if(m_data)
    {
        if(!--m_data->reference_count)
        {
          delete m_data          ;
                 m_data = nullptr;
        }
    }
}


const std::string&  type_info::get_id() const noexcept{return m_data->id;}


bool
type_info::
is_complete() const noexcept
{
    switch(m_data->kind)
    {
  case(type_kind::pointer):
  case(type_kind::reference):
  case(type_kind::array):
  case(type_kind::function_pointer):
  case(type_kind::boolean):
  case(type_kind::null_pointer):
  case(type_kind::generic_pointer):
  case(type_kind::integral):
  case(type_kind::unsigned_integral):
      return true;
      break;
  case(type_kind::const_qualified):
  case(type_kind::volatile_qualified):
  case(type_kind::const_volatile_qualified):
      return m_data->definition.ti.is_complete();
      break;
  case(type_kind::enum_):
      return m_data->definition.en->get_definition();
      break;
  case(type_kind::struct_):
      return m_data->definition.st->get_definition();
      break;
  case(type_kind::union_):
      return m_data->definition.un->get_definition();
      break;
    }
}


size_t
type_info::
get_size() const noexcept
{
    switch(m_data->kind)
    {
  case(type_kind::const_qualified):
  case(type_kind::volatile_qualified):
  case(type_kind::const_volatile_qualified):
      return m_data->definition.ti.get_size();
      break;
  case(type_kind::pointer):
  case(type_kind::reference):
  case(type_kind::null_pointer):
  case(type_kind::generic_pointer):
  case(type_kind::function_pointer):
      return pointer_type_size;
      break;
  case(type_kind::array):
      return m_data->definition.ti.get_size()*m_data->number_of_elements;
      break;
  case(type_kind::boolean):
  case(type_kind::integral):
  case(type_kind::unsigned_integral):
      return m_data->definition.size;
      break;
  case(type_kind::enum_):
      return word_type_size;
      break;
  case(type_kind::struct_):
      return m_data->definition.st->get_definition()->get_size();
      break;
  case(type_kind::union_):
      return m_data->definition.un->get_definition()->get_size();
      break;
    }
}


size_t
type_info::
get_align() const noexcept
{
    switch(m_data->kind)
    {
  case(type_kind::const_qualified):
  case(type_kind::volatile_qualified):
  case(type_kind::const_volatile_qualified):
      return m_data->definition.ti.get_align();
      break;
  case(type_kind::pointer):
  case(type_kind::reference):
  case(type_kind::null_pointer):
  case(type_kind::generic_pointer):
  case(type_kind::function_pointer):
      return pointer_type_size;
      break;
  case(type_kind::array):
      return m_data->definition.ti.get_align();
      break;
  case(type_kind::boolean):
  case(type_kind::integral):
  case(type_kind::unsigned_integral):
      return m_data->definition.size;
      break;
  case(type_kind::enum_):
      return word_type_size;
      break;
  case(type_kind::struct_):
      return m_data->definition.st->get_definition()->get_align();
      break;
  case(type_kind::union_):
      return m_data->definition.un->get_definition()->get_align();
      break;
    }
}


size_t  type_info::get_number_of_elements() const noexcept{return m_data->number_of_elements;}

type_kind  type_info::get_kind() const noexcept{return m_data->kind;}

const type_info&  type_info::get_source_type_info() const noexcept{return m_data->definition.ti;}

const   enum_definition*     type_info::get_enum_definition() const noexcept{return m_data->definition.en->get_definition();}
const struct_definition*   type_info::get_struct_definition() const noexcept{return m_data->definition.st->get_definition();}
const  union_definition*    type_info::get_union_definition() const noexcept{return m_data->definition.un->get_definition();}
const         signature*           type_info::get_signature() const noexcept{return &m_data->definition.sig;}




type_info
type_info::
make_array(size_t  n) const noexcept
{
  std::string  new_id(get_id());

  new_id += "a";
  new_id += std::to_string(n);

  return type_info(type_kind::array,new_id,*this,n);
}


}}




