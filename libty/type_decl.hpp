#ifndef type_decl_HPP
#define type_decl_HPP


#include"type_info.hpp"
#include"print.hpp"



namespace ty{
namespace ty_types{


constexpr
size_t
get_aligned_offset(size_t  offset, size_t  align) noexcept
{
    if(align)
    {
      offset = (offset+(align-1))/align*align;
    }


  return offset;
}


class
type_decl
{
  struct data;

  data*  m_data=nullptr;

  void  unrefer() noexcept;

public:
  type_decl(const type_info&  type_info, std::string_view  name) noexcept;
  type_decl(const type_decl&   rhs) noexcept{*this = rhs;}
  type_decl(      type_decl&&  rhs) noexcept{*this = std::move(rhs);}
 ~type_decl(){unrefer();}

  type_decl&  operator=(const type_decl&   rhs) noexcept;
  type_decl&  operator=(      type_decl&&  rhs) noexcept;

  const type_info&  get_info() const noexcept;

  const std::string&  get_name() const noexcept;

  void  print(FILE*  f) const noexcept;

};




}


using ty_types::type_decl;


}


#endif



