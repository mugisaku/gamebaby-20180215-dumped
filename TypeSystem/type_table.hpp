#ifndef type_table_HPP
#define type_table_HPP


#include"type.hpp"



namespace ts{
namespace type_tables{


struct type_was_not_found{};


const type*  append_type(types::type*  type, std::string_view  name) noexcept;

const type&  get_type(std::string_view  name);

type_info  get_type_info(std::string_view  name);

void  print_all_types(FILE*  f=stdout) noexcept;


}


using type_tables::append_type;
using type_tables::get_type;
using type_tables::get_type_info;
using type_tables::print_all_types;


}


#endif




