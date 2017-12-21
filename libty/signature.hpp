#ifndef signature_HPP
#define signature_HPP


#include"type_info.hpp"



namespace ty{
namespace ty_types{


struct
signature
{
  type_info  result_type_info;

  std::vector<type_info>  parameter_list;

  void  print(FILE*  f) const noexcept
  {
    
  }

};


}


using ty_types::signature;


}


#endif




