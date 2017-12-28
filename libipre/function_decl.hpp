#ifndef function_decl_HPP
#define function_decl_HPP


#include"libty/ty.hpp"
#include"libtok/stream_reader.hpp"
#include"stmt.hpp"
#include<list>



namespace ipre{
namespace ipre_types{


class
function_decl
{
  ty::signature  m_signature;

  std::string  m_name;

  std::vector<stmt>  m_stmt_list;

public:
  const ty::signature&  get_signature() const noexcept{return m_signasture;}

  const std::str8ing&  get_name() const noexcept{return m_name;}

};


}


using ipre_types::space;



}


#endif




