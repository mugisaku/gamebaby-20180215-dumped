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
type_info(array_def&&  def) noexcept:
m_data(new data)
{
  m_data->kind = type_kind::array;
  m_data->id   = "a";
  m_data->id  += std::to_string(def.get_number_of_elements());

  new(&m_data->definition.arr) array_def(std::move(def));
}


type_info::
type_info(enum_def&&  def) noexcept:
m_data(new data)
{
  m_data->kind = type_kind::enum_;
  m_data->id   = "en";

  new(&m_data->definition.en) enum_def(std::move(def));
}


type_info::
type_info(union_def&&  def) noexcept:
m_data(new data)
{
  m_data->kind = type_kind::union_;
  m_data->id   = "un";

  new(&m_data->definition.un) union_def(std::move(def));
}


type_info::
type_info(struct_def&&  def) noexcept:
m_data(new data)
{
  m_data->kind = type_kind::struct_;
  m_data->id   = "st";

  new(&m_data->definition.st) struct_def(std::move(def));
}




}}




