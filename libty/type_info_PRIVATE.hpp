#ifndef type_info_PRIVATE_HPP
#define type_info_PRIVATE_HPP


#include"type_info.hpp"


namespace ty{
namespace types{


struct
type_info::
data
{
  size_t  reference_count;

  type_kind  kind;

  std::string  id;

  size_t   size;
  size_t  align;

  size_t  number_of_elements;

  type_info  source;

};


}}


#endif




