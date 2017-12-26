#ifndef TOK_HPP
#define TOK_HPP


#include"token.hpp"
#include<vector>
#include<cstdio>


namespace tok{
namespace tok_types{


using token_list = std::vector<token>;

token_list  make_token_list_from_string(std::string_view  sv);

token_list  make_token_list_from_file(const char*  path);
token_list  make_token_list_from_file(FILE*  f);


}


using tok_types::token_list;

using tok_types::make_token_list_from_string;
using tok_types::make_token_list_from_file;


}


#endif




