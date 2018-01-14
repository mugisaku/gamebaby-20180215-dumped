#include"libgbsnd/execution.hpp"
#include"libgbsnd/stmt.hpp"
#include"libgbsnd/object.hpp"


namespace gbsnd{
namespace devices{


const object*
execution_frame::
find_object(gbstd::string_view  name) const noexcept
{
    for(auto&  o: m_object_list)
    {
        if(o.get_name() == name)
        {
          return &o;
        }
    }


  return nullptr;
}


const stmt*
execution_frame::
get_stmt() noexcept
{
  return m_stmt_list+m_pc++;
}


}}




