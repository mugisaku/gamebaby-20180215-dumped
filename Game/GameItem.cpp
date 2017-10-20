#include"GameItem.hpp"


namespace gmbb{




bool
GameItem::
operator<(GameItem const&  rhs) const noexcept
{
    if(specs)
    {
        if(rhs.specs)
        {
            if(( is_equipped() &&  rhs.is_equipped()) ||
               (!is_equipped() && !rhs.is_equipped()))
            {
              return (specs < rhs.specs);
            }


          return is_equipped();
        }


      return true;
    }


  return false;
}



}




