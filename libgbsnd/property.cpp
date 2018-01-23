#include"libgbsnd/object.hpp"
#include<new>


namespace gbsnd{
namespace devices{




value  property::get(               ) const noexcept{return m_getter(*m_object  );}
void   property::set(const value&  v) const noexcept{       m_setter(*m_object,v);}




}}




