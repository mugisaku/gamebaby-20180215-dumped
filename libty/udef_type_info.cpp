#include"udef_type_info.hpp"
#include<new>



namespace ty{
namespace ty_types{




udef_type_info::
udef_type_info(array_def&&  arr) noexcept:
m_kind(udef_type_kind::array){new(&m_set) array_def(std::move(arr));}


udef_type_info::
udef_type_info(struct_def&&  st) noexcept:
m_kind(udef_type_kind::struct_){new(&m_set) struct_def(std::move(st));}


udef_type_info::
udef_type_info(enum_def&&  en) noexcept:
m_kind(udef_type_kind::enum_){new(&m_set) enum_def(std::move(en));}


udef_type_info::
udef_type_info(union_def&&  un) noexcept:
m_kind(udef_type_kind::union_){new(&m_set) union_def(std::move(un));}




udef_type_info&
udef_type_info::
operator=(const udef_type_info&  rhs) noexcept
{
  clear();

  m_kind = rhs.m_kind;

    switch(m_kind)
    {
  case(udef_type_kind::array):
      new(&m_set) array_def(rhs.m_set.arr);
      break;
  case(udef_type_kind::struct_):
      new(&m_set) struct_def(rhs.m_set.st);
      break;
  case(udef_type_kind::enum_):
      new(&m_set) enum_def(rhs.m_set.en);
      break;
  case(udef_type_kind::union_):
      new(&m_set) union_def(rhs.m_set.un);
      break;
    }


  return *this;
}


udef_type_info&
udef_type_info::
operator=(udef_type_info&&  rhs) noexcept
{
  clear();

  std::swap(m_kind,rhs.m_kind);

    switch(m_kind)
    {
  case(udef_type_kind::array):
      new(&m_set) array_def(std::move(rhs.m_set.arr));
      break;
  case(udef_type_kind::struct_):
      new(&m_set) struct_def(std::move(rhs.m_set.st));
      break;
  case(udef_type_kind::enum_):
      new(&m_set) enum_def(std::move(rhs.m_set.en));
      break;
  case(udef_type_kind::union_):
      new(&m_set) union_def(std::move(rhs.m_set.un));
      break;
    }


  return *this;
}




void
udef_type_info::
clear() noexcept
{
    switch(m_kind)
    {
  case(udef_type_kind::array):
      m_set.arr.~array_def();
      break;
  case(udef_type_kind::struct_):
      m_set.st.~struct_def();
      break;
  case(udef_type_kind::enum_):
      m_set.en.~enum_def();
      break;
  case(udef_type_kind::union_):
      m_set.un.~union_def();
      break;
    }


  m_kind = udef_type_kind::null;
}


const std::string&
udef_type_info::
get_id() const noexcept
{
  static const std::string  arr_s("arr");
  static const std::string  en_s("en");
  static const std::string  st_s("st");
  static const std::string  un_s("un");

    switch(m_kind)
    {
  case(udef_type_kind::array  ): return arr_s;break;
  case(udef_type_kind::struct_): return st_s;break;
  case(udef_type_kind::enum_  ): return en_s;break;
  case(udef_type_kind::union_ ): return un_s;break;
    }
}


size_t
udef_type_info::
get_size() const noexcept
{
  size_t  sz = 0;

    switch(m_kind)
    {
  case(udef_type_kind::array  ): sz = m_set.arr.get_size();break;
  case(udef_type_kind::struct_): sz = m_set.st.get_size();break;
  case(udef_type_kind::enum_  ): sz = m_set.en.get_size();break;
  case(udef_type_kind::union_ ): sz = m_set.un.get_size();break;
    }


  return get_aligned_offset(sz,get_align());
}


size_t
udef_type_info::
get_align() const noexcept
{
    switch(m_kind)
    {
  case(udef_type_kind::array  ): return m_set.arr.get_align();
  case(udef_type_kind::struct_): return m_set.st.get_align();
  case(udef_type_kind::enum_  ): return m_set.en.get_align();
  case(udef_type_kind::union_ ): return m_set.un.get_align();
    }


  return 0;
}


void
udef_type_info::
print(FILE*  f) const noexcept
{
    switch(m_kind)
    {
  case(udef_type_kind::array):
      m_set.arr.print(f);
      break;
  case(udef_type_kind::struct_):
      fprintf(f,"struct");
     break;
  case(udef_type_kind::enum_):
      fprintf(f,"enum");
     break;
  case(udef_type_kind::union_):
      fprintf(f,"union");
      break;
    }
}


}}




