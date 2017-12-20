#include"type_info_PRIVATE.hpp"



namespace ts{
namespace types{



const type_info&           type_info::remove_const() const noexcept{return          is_const()? m_data->source:*this;}
const type_info&        type_info::remove_volatile() const noexcept{return       is_volatile()? m_data->source:*this;}
const type_info&  type_info::remove_const_volatile() const noexcept{return is_const_volatile()? m_data->source:*this;}
const type_info&         type_info::remove_pointer() const noexcept{return        is_pointer()? m_data->source:*this;}
const type_info&       type_info::remove_reference() const noexcept{return      is_reference()? m_data->source:*this;}




}}




