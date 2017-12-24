#include"type_info_PRIVATE.hpp"



namespace ty{
namespace ty_types{


bool  type_info::              is_const() const noexcept{return (m_data->m_qualification_flags&const_flag);}
bool  type_info::           is_volatile() const noexcept{return (m_data->m_qualification_flags&volatile_flag);}
bool  type_info::     is_const_volatile() const noexcept{return is_const()&&is_volatile();}
bool  type_info::           is_integral() const noexcept{return m_data->m_kind == type_kind::integral;}
bool  type_info::  is_unsigned_integral() const noexcept{return m_data->m_kind == type_kind::unsigned_integral;}
bool  type_info::            is_boolean() const noexcept{return m_data->m_kind == type_kind::boolean;}
bool  type_info::               is_void() const noexcept{return m_data->m_kind == type_kind::void_;}
bool  type_info::            is_pointer() const noexcept{return m_data->m_kind == type_kind::pointer;}
bool  type_info::       is_null_pointer() const noexcept{return m_data->m_kind == type_kind::null_pointer;}
bool  type_info::    is_generic_pointer() const noexcept{return m_data->m_kind == type_kind::generic_pointer;}
bool  type_info::   is_function_pointer() const noexcept{return m_data->m_kind == type_kind::function_pointer;}
bool  type_info::          is_reference() const noexcept{return m_data->m_kind == type_kind::reference;}
bool  type_info::   is_rvalue_reference() const noexcept{return m_data->m_kind == type_kind::rvalue_reference;}
bool  type_info::             is_struct() const noexcept{return m_data->m_kind == type_kind::struct_;}
bool  type_info::               is_enum() const noexcept{return m_data->m_kind == type_kind::enum_;}
bool  type_info::              is_union() const noexcept{return m_data->m_kind == type_kind::union_;}
bool  type_info::              is_array() const noexcept{return m_data->m_kind == type_kind::array;}



}}




