#ifndef pointer_type_info_HPP
#define pointer_type_info_HPP


#include<cstddef>
#include<cstdint>
#include<cstdio>
#include<string>



namespace ts{
namespace types{


class type_info;


enum class
pointer_kind
{
  null,
  generic,
  defined,

};


class
pointer_type_info
{
  pointer_kind  m_kind;

  const type_info*  m_target;

public:
  constexpr pointer_type_info(pointer_kind  kind) noexcept:
  m_kind(kind),
  m_target(nullptr){}

  constexpr pointer_type_info(const type_info&  target) noexcept:
  m_kind(pointer_kind::defined),
  m_target(&target){}

  constexpr bool  is_null() const noexcept{return m_kind == pointer_kind::null;}
  constexpr bool  is_generic() const noexcept{return m_kind == pointer_kind::generic;}
  constexpr bool  is_defined() const noexcept{return m_kind == pointer_kind::defined;}

  constexpr const type_info&   get_target() const noexcept{return *m_target;}

  static constexpr size_t  get_size() noexcept{return 4;}

};


}


using types::pointer_type_info;
using types::pointer_kind;


}


#endif




