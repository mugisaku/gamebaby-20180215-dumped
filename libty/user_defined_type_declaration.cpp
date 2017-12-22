#include"user_defined_type_declaration.hpp"
#include<new>



namespace ty{
namespace ty_types{




user_defined_type_declaration::
user_defined_type_declaration(array_definition&&  arr) noexcept:
m_kind(user_defined_type_kind::array){new(&m_set) array_definition(std::move(arr));}


user_defined_type_declaration::
user_defined_type_declaration(struct_definition&&  st) noexcept:
m_kind(user_defined_type_kind::struct_){new(&m_set) struct_definition(std::move(st));}


user_defined_type_declaration::
user_defined_type_declaration(enum_definition&&  en) noexcept:
m_kind(user_defined_type_kind::enum_){new(&m_set) enum_definition(std::move(en));}


user_defined_type_declaration::
user_defined_type_declaration(union_definition&&  un) noexcept:
m_kind(user_defined_type_kind::union_){new(&m_set) union_definition(std::move(un));}




user_defined_type_declaration&
user_defined_type_declaration::
operator=(const user_defined_type_declaration&  rhs) noexcept
{
  clear();

  m_kind = rhs.m_kind;

    switch(m_kind)
    {
  case(user_defined_type_kind::array):
      new(&m_set) array_definition(rhs.m_set.arr);
      break;
  case(user_defined_type_kind::struct_):
      new(&m_set) struct_definition(rhs.m_set.st);
      break;
  case(user_defined_type_kind::enum_):
      new(&m_set) enum_definition(rhs.m_set.en);
      break;
  case(user_defined_type_kind::union_):
      new(&m_set) union_definition(rhs.m_set.un);
      break;
    }


  return *this;
}


user_defined_type_declaration&
user_defined_type_declaration::
operator=(user_defined_type_declaration&&  rhs) noexcept
{
  clear();

  std::swap(m_kind,rhs.m_kind);

    switch(m_kind)
    {
  case(user_defined_type_kind::array):
      new(&m_set) array_definition(std::move(rhs.m_set.arr));
      break;
  case(user_defined_type_kind::struct_):
      new(&m_set) struct_definition(std::move(rhs.m_set.st));
      break;
  case(user_defined_type_kind::enum_):
      new(&m_set) enum_definition(std::move(rhs.m_set.en));
      break;
  case(user_defined_type_kind::union_):
      new(&m_set) union_definition(std::move(rhs.m_set.un));
      break;
    }


  return *this;
}




void
user_defined_type_declaration::
clear() noexcept
{
    switch(m_kind)
    {
  case(user_defined_type_kind::array):
      m_set.arr.~array_definition();
      break;
  case(user_defined_type_kind::struct_):
      m_set.st.~struct_definition();
      break;
  case(user_defined_type_kind::enum_):
      m_set.en.~enum_definition();
      break;
  case(user_defined_type_kind::union_):
      m_set.un.~union_definition();
      break;
    }


  m_kind = user_defined_type_kind::null;
}


const std::string&
user_defined_type_declaration::
get_id() const noexcept
{
  static const std::string  arr_s("arr");
  static const std::string  en_s("en");
  static const std::string  st_s("st");
  static const std::string  un_s("un");

    switch(m_kind)
    {
  case(user_defined_type_kind::array  ): return arr_s;break;
  case(user_defined_type_kind::struct_): return st_s;break;
  case(user_defined_type_kind::enum_  ): return en_s;break;
  case(user_defined_type_kind::union_ ): return un_s;break;
    }
}


size_t
user_defined_type_declaration::
get_size() const noexcept
{
  size_t  sz = 0;

    switch(m_kind)
    {
  case(user_defined_type_kind::array  ): sz = m_set.arr.get_size();break;
  case(user_defined_type_kind::struct_): sz = m_set.st.get_size();break;
  case(user_defined_type_kind::enum_  ): sz = m_set.en.get_size();break;
  case(user_defined_type_kind::union_ ): sz = m_set.un.get_size();break;
    }


  return get_aligned_offset(sz,get_align());
}


size_t
user_defined_type_declaration::
get_align() const noexcept
{
    switch(m_kind)
    {
  case(user_defined_type_kind::array  ): return m_set.arr.get_align();
  case(user_defined_type_kind::struct_): return m_set.st.get_align();
  case(user_defined_type_kind::enum_  ): return m_set.en.get_align();
  case(user_defined_type_kind::union_ ): return m_set.un.get_align();
    }


  return 0;
}


void
user_defined_type_declaration::
print(FILE*  f, size_t  offset_base) const noexcept
{
    switch(m_kind)
    {
  case(user_defined_type_kind::array):
      {
        auto&  arr = m_set.arr;

        arr.get_element_type_info().print_human_readable(f,offset_base);

        fprintf(f,"[%zu]",arr.get_number_of_elements());
      }
      break;
  case(user_defined_type_kind::struct_):
      fprintf(f,"struct ");

      m_set.st.print(f,offset_base);
      break;
  case(user_defined_type_kind::enum_):
      fprintf(f,"enum ");
      m_set.en.print(f);
      break;
  case(user_defined_type_kind::union_):
      fprintf(f,"union ");
      m_set.un.print(f);
      break;
    }
}


}}




