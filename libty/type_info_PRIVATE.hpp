#ifndef type_info_PRIVATE_HPP
#define type_info_PRIVATE_HPP


#include"type_info.hpp"
#include"enum_definition.hpp"
#include"struct_definition.hpp"
#include"union_definition.hpp"
#include"signature.hpp"


namespace ty{
namespace ty_types{


struct
type_info::
data
{
  size_t  reference_count;

  type_kind  kind;

  std::string  id;

  size_t  number_of_elements;

  union definition_t{
    size_t  size;

    type_info  ti;

    const enum_declaration*     en;
    const struct_declaration*   st;
    const union_declaration*    un;

    signature  sig;

    definition_t(){}
   ~definition_t(){}

  } definition;


  ~data()
  {
      switch(kind)
      {
    case(type_kind::const_qualified):
    case(type_kind::volatile_qualified):
    case(type_kind::const_volatile_qualified):
    case(type_kind::pointer):
    case(type_kind::reference):
    case(type_kind::array):
        definition.ti.~type_info();
        break;
    case(type_kind::boolean):
    case(type_kind::null_pointer):
    case(type_kind::generic_pointer):
    case(type_kind::integral):
    case(type_kind::unsigned_integral):
    case(type_kind::enum_):
    case(type_kind::struct_):
    case(type_kind::union_):
        break;
    case(type_kind::function_pointer):
        definition.sig.~signature();
        break;
      }
  }

};


}}


#endif




