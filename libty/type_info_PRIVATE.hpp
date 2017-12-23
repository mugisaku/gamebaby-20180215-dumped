#ifndef type_info_PRIVATE_HPP
#define type_info_PRIVATE_HPP


#include"type_info.hpp"
#include"array_def.hpp"
#include"enum_def.hpp"
#include"struct_def.hpp"
#include"union_def.hpp"
#include"signature.hpp"


namespace ty{
namespace ty_types{


struct
type_info::
data
{
  size_t  reference_count=1;

  type_kind  kind=type_kind::null;

  std::string  id;

  union definition_t{
    size_t  size;

    type_info  ti;

     array_def  arr;
      enum_def   en;
    struct_def   st;
     union_def   un;

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
        definition.ti.~type_info();
        break;
    case(type_kind::boolean):
    case(type_kind::null_pointer):
    case(type_kind::generic_pointer):
    case(type_kind::integral):
    case(type_kind::unsigned_integral):
        break;
    case(type_kind::function_pointer): definition.sig.~signature();break;
    case(type_kind::array           ): definition.arr.~array_def();break;
    case(type_kind::struct_         ): definition.st.~struct_def();break;
    case(type_kind::enum_           ): definition.en.~enum_def();break;
    case(type_kind::union_          ): definition.un.~union_def();break;
        }
  }


};


}}


#endif




