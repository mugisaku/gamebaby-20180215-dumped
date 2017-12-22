#include"type_info_PRIVATE.hpp"
#include<new>



namespace ty{
namespace ty_types{




type_info::
type_info(type_kind  kind, std::string_view  id, size_t  size) noexcept:
m_data(new data)
{
  m_data->kind = kind;
  m_data->id   =   id;

  m_data->definition.size = size;
}


type_info::
type_info(type_kind  kind, std::string_view  id, const type_info&  source) noexcept:
m_data(new data)
{
  m_data->kind = kind;
  m_data->id   =   id;

  new(&m_data->definition) type_info(source);
}


type_info::
type_info(user_defined_type_declaration&&  decl) noexcept:
m_data(new data)
{
  m_data->kind = type_kind::user_defined;
  m_data->id   =           decl.get_id();

  new(&m_data->definition.decl) user_defined_type_declaration(std::move(decl));
}




type_info&
type_info::
operator=(const type_info&  rhs) noexcept
{
    if(&rhs != this)
    {
      unrefer();

      m_data = rhs.m_data;

        if(m_data)
        {
          ++m_data->reference_count;
        }
    }


  return *this;
}


type_info&
type_info::
operator=(type_info&&  rhs) noexcept
{
    if(&rhs != this)
    {
      unrefer();

      m_data = rhs.m_data          ;
               rhs.m_data = nullptr;
    }


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
  case(type_kind::boolean):
  case(type_kind::integral):
  case(type_kind::unsigned_integral):
      return m_data->definition.size;
      break;
  case(type_kind::user_defined):
      return m_data->definition.decl.get_size();
      break;
    }


  return 0;
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
  case(type_kind::boolean):
  case(type_kind::integral):
  case(type_kind::unsigned_integral):
      return m_data->definition.size;
      break;
  case(type_kind::user_defined):
      return m_data->definition.decl.get_align();
      break;
    }


  return 0;
}


type_kind  type_info::get_kind() const noexcept{return m_data->kind;}

const type_info&  type_info::get_source_type_info() const noexcept{return m_data->definition.ti;}


const user_defined_type_declaration&
type_info::
get_user_defined_type_declaration() const noexcept
{
  return m_data->definition.decl;
}


}}




