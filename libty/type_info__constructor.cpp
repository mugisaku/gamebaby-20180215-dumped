#include"type_info_PRIVATE.hpp"
#include<new>



namespace ty{
namespace ty_types{




type_info::
type_info(std::string_view  id, type_kind  kind, size_t  size) noexcept:
m_data(new data)
{
  m_data->m_id   =   id;
  m_data->m_kind = kind;

  m_data->m_set.size = size;
}


type_info::
type_info(std::string_view  id, type_kind  kind, const type_info&  source) noexcept:
m_data(new data)
{
  m_data->m_id   =   id;
  m_data->m_kind = kind;

  new(&m_data->m_set) type_info(source);
}


type_info::
type_info(array_def&&  def) noexcept:
m_data(new data)
{
  m_data->m_id   = "a";
  m_data->m_id  += std::to_string(def.get_number_of_elements());
  m_data->m_kind = type_kind::array;

  new(&m_data->m_set.arr) array_def(std::move(def));
}


type_info::
type_info(enum_def&&  def) noexcept:
m_data(new data)
{
  m_data->m_id   = "en";
  m_data->m_kind = type_kind::enum_;

  new(&m_data->m_set.en) enum_def(std::move(def));
}


type_info::
type_info(union_def&&  def) noexcept:
m_data(new data)
{
  m_data->m_id   = "un";
  m_data->m_kind = type_kind::union_;

  new(&m_data->m_set.un) union_def(std::move(def));
}


type_info::
type_info(struct_def&&  def) noexcept:
m_data(new data)
{
  m_data->m_id   = "st";
  m_data->m_kind = type_kind::struct_;

  new(&m_data->m_set.st) struct_def(std::move(def));
}




}}




