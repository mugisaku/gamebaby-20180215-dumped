#ifndef signature_HPP
#define signature_HPP


#include"type_info.hpp"



namespace ty{
namespace ty_types{


class
signature
{
  type_info  m_result_type_info;

  std::vector<type_info>  m_type_info_list;

  bool  m_varargs_flag=false;

public:
  signature(                           ) noexcept{}
  signature(const type_info&  result_ti, std::initializer_list<type_info>  ls={}, bool  varargs_flag=false) noexcept:
  m_result_type_info(result_ti),
  m_type_info_list(ls),
  m_varargs_flag(varargs_flag){}


  void  append(const type_info&  ti) noexcept{m_type_info_list.emplace_back(ti);}

  void              set_result_type_info(const type_info&  ti)       noexcept{m_result_type_info = ti;}
  const type_info&  get_result_type_info(                    ) const noexcept{return m_result_type_info;}

  const std::vector<type_info>&  get_type_info_list() const noexcept{return m_type_info_list;}

  bool  test_varargs_flag() const noexcept{return m_varargs_flag;}

  void  print(FILE*  f) const noexcept
  {
    m_result_type_info.print(f);

    fprintf(f,"(*)(");

      for(auto&  ti: m_type_info_list)
      {
        ti.print(f);

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




