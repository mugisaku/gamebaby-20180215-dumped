#ifndef stmt_HPP
#define stmt_HPP


#include"libty/ty.hpp"
#include"libtok/stream_reader.hpp"
#include"block.hpp"
#include<list>



namespace ipre{
namespace ipre_types{


class
stmt
{
  enum class kind{
    null,
    type_decl,
    type_def,
    function_decl,
    function_def,
  } m_kind=kind::null;

  union data{
    ty::type_decl  td;

    std::string_view  sv;

    data(){}
   ~data(){}
  } m_data;


  stmt*  m_next=nullptr;

public:
  stmt() noexcept{}
  stmt(const ty::type_decl&  td, bool  is_def) noexcept;
  stmt(const stmt&   rhs) noexcept{*this = rhs;}
  stmt(      stmt&&  rhs) noexcept{*this = std::move(rhs);}
 ~stmt(){clear();}

  stmt&  operator=(const stmt&   rhs) noexcept;
  stmt&  operator=(      stmt&&  rhs) noexcept;

  void  clear() noexcept;

  const stmt*  get_next() const noexcept{return m_next;;}
  void         set_next(stmt*  next) noexcept{m_next = next;}

};


}


using ipre_types::stmt;



}


#endif




