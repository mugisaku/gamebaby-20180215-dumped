#ifndef signature_HPP
#define signature_HPP


#include"type_decl.hpp"



namespace ty{
namespace ty_types{


class
signature
{
  type_decl  m_result_type_decl;

  std::vector<type_decl>  m_type_decl_list;

  bool  m_varargs_flag=false;

public:
  signature(const type_decl&  result_td, std::initializer_list<type_decl>  ls={}, bool  varargs_flag=false) noexcept:
  m_result_type_decl(result_td),
  m_type_decl_list(ls),
  m_varargs_flag(varargs_flag){}


  void  append(const type_decl&  td) noexcept{m_type_decl_list.emplace_back(td);}

  void              set_result_type_decl(const type_decl&  td)       noexcept{m_result_type_decl = td;}
  const type_decl&  get_result_type_decl(                    ) const noexcept{return m_result_type_decl;}

  const std::vector<type_decl>&  get_type_decl_list() const noexcept{return m_type_decl_list;}

  bool  test_varargs_flag() const noexcept{return m_varargs_flag;}

  void  print(FILE*  f) const noexcept
  {
    m_result_type_decl.print(f);

    fprintf(f,"(*)(");

      for(auto&  td: m_type_decl_list)
      {
        td.print(f);

        fprintf(f,", ");
      }


      if(m_varargs_flag)
      {
        fprintf(f,"...");
      }


    fprintf(f,")");
  }

};


}


using ty_types::signature;


}


#endif




