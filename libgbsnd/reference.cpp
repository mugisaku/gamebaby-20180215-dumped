#include"libgbsnd/object.hpp"
#include"libgbsnd/script.hpp"
#include<new>


namespace gbsnd{
namespace devices{


property
reference::
get_property(const identifier&  id) const noexcept
{
  auto&  obj = *m_pointer;

    if(obj.is_square_wave())
    {
      return obj.get_square_wave().get_property(id.view());
    }
}


}}




