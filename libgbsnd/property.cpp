#include"libgbsnd/object.hpp"
#include<new>


namespace gbsnd{
namespace devices{




value  property::get(               ) const noexcept{return m_accessor.getter(m_object->get_value()  );}
void   property::set(const value&  v) const noexcept{       m_accessor.setter(m_object->get_value(),v);}




}}




