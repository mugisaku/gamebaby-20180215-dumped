#ifndef signature_HPP
#define signature_HPP


#include"type_info.hpp"



namespace ty{
namespace definitiions{


class
signature
{
  type_info  m_result;

  std::vector<type_info>  m_parameter_list;

public:
  signature(const type_info&  result, std::vector<type_info>&&  ls) noexcept:
  m_result(result),
  m_parameter_list(std::move(ls)){}

  const type_info&  get_result_type_info() const noexcept{return m_result;}

  const std::vector<type_info>&  get_parameter_list() const noexcept{return m_parameter_list;}

};


}


using definitions::signature;


}


#endif




