#include"libgbsnd/routine.hpp"
#include"libgbsnd/stmt.hpp"


namespace gbsnd{
namespace devices{




struct
routine::
data
{
  size_t  m_reference_count=1;

  parameter_list  m_parameter_list;

  block*  m_block=nullptr;

  ~data()
  {
    delete m_block;
  }

};


routine::
routine() noexcept:
m_data(new data)
{
}




routine&
routine::
operator=(const routine&   rhs) noexcept
{
  unrefer();

  m_data = rhs.m_data;

    if(m_data)
    {
      ++m_data->m_reference_count;
    }


  return *this;
}


routine&
routine::
operator=(routine&&  rhs) noexcept
{
  unrefer();

  std::swap(m_data,rhs.m_data);

  return *this;
}


void
routine::
unrefer() noexcept
{
    if(m_data)
    {
      auto&  n = m_data->m_reference_count;

        if(!--n)
        {
          delete m_data          ;
                 m_data = nullptr;
        }
    }
}


const parameter_list&
routine::
get_parameter_list() const noexcept
{
  return m_data->m_parameter_list;
}


const block*
routine::
get_block() const noexcept
{
  return m_data->m_block;
}


}}




