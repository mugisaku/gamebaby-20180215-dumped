#ifndef union_def_HPP
#define union_def_HPP


#include<cstdint>
#include<vector>
#include"var_decl.hpp"



namespace ty{
namespace ty_types{


class type_info;


struct
union_def
{
  std::vector<var_decl>  m_decl_list;

  size_t  m_size =0;
  size_t  m_align=0;

public:
  union_def() noexcept{}

  void  append(const type_decl&  td, gbstd::string  name) noexcept;

  size_t   get_size() const noexcept{return m_size;}
  size_t  get_align() const noexcept{return m_align;}

  void  print(FILE*  f=stdout) const noexcept;

};


}


using ty_types::union_def;


}


#endif




