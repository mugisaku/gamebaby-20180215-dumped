#include"type_info_PRIVATE.hpp"
#include<new>



namespace ty{
namespace ty_types{




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


template<typename  T>
size_t
get_aligned_size(const T&  t) noexcept
{
  return get_aligned_offset(t.get_size(),t.get_align());
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
  case(type_kind::rvalue_reference):
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
  case(type_kind::array  ): return get_aligned_size(m_data->definition.arr);break;
  case(type_kind::struct_): return get_aligned_size(m_data->definition.st );break;
  case(type_kind::enum_  ): return get_aligned_size(m_data->definition.en );break;
  case(type_kind::union_ ): return get_aligned_size(m_data->definition.un );break;
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
  case(type_kind::rvalue_reference):
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
  case(type_kind::array  ): return m_data->definition.arr.get_align();
  case(type_kind::struct_): return m_data->definition.st.get_align();
  case(type_kind::enum_  ): return m_data->definition.en.get_align();
  case(type_kind::union_ ): return m_data->definition.un.get_align();
    }


  return 0;
}


bool
type_info::
test_align(size_t  offset_base) const noexcept
{
  auto  a = get_align();

    if(!a || (offset_base%a))
    {
      return false;
    }


    switch(m_data->kind)
    {
  case(type_kind::const_qualified):
  case(type_kind::volatile_qualified):
  case(type_kind::const_volatile_qualified):
  case(type_kind::pointer):
  case(type_kind::reference):
  case(type_kind::rvalue_reference):
  case(type_kind::null_pointer):
  case(type_kind::generic_pointer):
  case(type_kind::function_pointer):
  case(type_kind::boolean):
  case(type_kind::integral):
  case(type_kind::unsigned_integral):
  case(type_kind::array):
  case(type_kind::enum_):
  case(type_kind::union_):
      return true;
      break;
  case(type_kind::struct_):
      return m_data->definition.st.test_align(offset_base);
      break;
    }


  return false;
}




type_kind  type_info::get_kind() const noexcept{return m_data->kind;}

const type_info&  type_info::get_source_type_info() const noexcept{return m_data->definition.ti;}
const  array_def&   type_info::get_array_def() const noexcept{return m_data->definition.arr;}

struct_def&  type_info::get_struct_def() const noexcept{return m_data->definition.st;}
  enum_def&    type_info::get_enum_def() const noexcept{return m_data->definition.en;}
 union_def&   type_info::get_union_def() const noexcept{return m_data->definition.un;}


type_info  type_info::make_array(const type_info&  ti, size_t  n)  noexcept{return type_info(array_def(ti,n));}
type_info  type_info::make_empty_enum()   noexcept{return type_info(  enum_def());}
type_info  type_info::make_empty_struct() noexcept{return type_info(struct_def());}
type_info  type_info::make_empty_union()  noexcept{return type_info( union_def());}




}}




