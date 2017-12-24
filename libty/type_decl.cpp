#include"type_decl_PRIVATE.hpp"



namespace ty{
namespace ty_types{




type_decl::
type_decl(const type_info&  type_info, std::string_view  name) noexcept:
m_data(new data)
{
  m_data->m_type_info = type_info;
  m_data->m_name      =      name;
}




type_decl&
type_decl::
operator=(const type_decl&  rhs) noexcept
{
    if(&rhs != this)
    {
      unrefer();

      m_data = rhs.m_data;

        if(m_data)
        {
          ++m_data->m_reference_count;
        }
    }


  return *this;
}


type_decl&
type_decl::
operator=(type_decl&&  rhs) noexcept
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
type_decl::
unrefer() noexcept
{
    if(m_data)
    {
        if(!--m_data->m_reference_count)
        {
          delete m_data          ;
                 m_data = nullptr;
        }
    }
}




const type_info&  type_decl::get_info() const noexcept{return m_data->m_type_info;}

const std::string&  type_decl::get_name() const noexcept{return m_data->m_name;}


void
type_decl::
print(FILE*  f) const noexcept
{
  fprintf(f,"%s",m_data->m_name.data());
}


}}




