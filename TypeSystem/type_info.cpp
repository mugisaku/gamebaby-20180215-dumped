#include"type_info_PRIVATE.hpp"



namespace ts{
namespace types{




type_info::
type_info(type_kind  kind, std::string_view  id, size_t  size, size_t  align) noexcept:
m_data(new data)
{
  m_data->reference_count = 1;

  m_data->kind = kind;

  m_data->id = id;
  m_data->size = size;
  m_data->align = align;
  m_data->number_of_elements = 1;
}


type_info::
type_info(type_kind  kind, std::string_view  id, const type_info&  source) noexcept:
m_data(new data)
{
  m_data->reference_count = 1;

  m_data->kind = kind;
/*
  m_data->id = id;
  m_data->size = source.get_size();
  m_data->align = align;
  m_data->number_of_elements = number_of_elements;

    if(source)
    {
      m_data->source = *source;
    }
*/
}


type_info::
type_info(type_kind  kind, std::string_view  id, const type_info&  source, size_t  number_of_elements) noexcept:
m_data(new data)
{
  m_data->reference_count = 1;

  m_data->kind = kind;
/*
  m_data->id = id;
  m_data->size = source.get_size();
  m_data->align = align;
  m_data->number_of_elements = number_of_elements;

    if(source)
    {
      m_data->source = *source;
    }
*/
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

size_t   type_info::get_size() const noexcept{return m_data->size;}
size_t  type_info::get_align() const noexcept{return m_data->align;}
size_t  type_info::get_number_of_elements() const noexcept{return m_data->number_of_elements;}

type_kind  type_info::get_kind() const noexcept{return m_data->kind;}




type_info
type_info::
make_array(size_t  n) const noexcept
{
  return type_info();
}


}}




