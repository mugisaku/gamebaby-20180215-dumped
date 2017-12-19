#ifndef type_table_HPP
#define type_table_HPP


#include"type_info.hpp"



namespace ts{
namespace types{


struct type_was_not_found{};


extern const type_info        s8_ti;
extern const type_info        u8_ti;
extern const type_info       s16_ti;
extern const type_info       u16_ti;
extern const type_info       s32_ti;
extern const type_info       u32_ti;
extern const type_info      bool_ti;
extern const type_info      void_ti;
extern const type_info   nullptr_ti;
extern const type_info   geneptr_ti;


const type_info&  append_type_info(type_info&&  type_info) noexcept;

void  name_type_info(const type_info&  type_info, std::string_view  name) noexcept;

const type_info&  get_type_info_by_name(std::string_view  name);
const type_info&  get_type_info_by_id(std::string_view  id);

void  print_all_types(FILE*  f=stdout) noexcept;


}


using types::s8_ti;
using types::u8_ti;
using types::s16_ti;
using types::u16_ti;
using types::s32_ti;
using types::u32_ti;
using types::bool_ti;
using types::void_ti;
using types::nullptr_ti;
using types::geneptr_ti;

using types::append_type_info;
using types::name_type_info;
using types::get_type_info_by_name;
using types::get_type_info_by_id;
using types::print_all_types;


}


#endif




