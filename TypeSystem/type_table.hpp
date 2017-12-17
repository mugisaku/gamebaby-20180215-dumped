#ifndef type_table_HPP
#define type_table_HPP


#include"type.hpp"



namespace ts{
namespace type_tables{


struct type_was_not_found{};


const type*  append_type(types::type*  type, std::string_view  name) noexcept;

const type&  get_type_by_name(std::string_view  name);
const type&  get_type_by_index(type_index  i);

const type_info&  get_type_info_by_name(std::string_view  name);
const type_info&  get_type_info_by_index(type_index  i);

void  print_all_types(FILE*  f=stdout) noexcept;


}


using type_tables::append_type;
using type_tables::get_type_by_name;
using type_tables::get_type_by_index;
using type_tables::get_type_info_by_name;
using type_tables::get_type_info_by_index;
using type_tables::print_all_types;


}


#endif




