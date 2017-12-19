#ifndef pointer_type_info_HPP
#define pointer_type_info_HPP


#include<cstddef>
#include<cstdint>
#include<cstdio>
#include<string>



namespace ts{
namespace types{


class type_info;


constexpr size_t  pointer_type_size = 4;


class
null_pointer_type_info
{
public:
  constexpr null_pointer_type_info() noexcept{}

};


class
generic_pointer_type_info
{
public:
  constexpr generic_pointer_type_info() noexcept{}

};


class
pointer_type_info
{
  const type_info*  m_target;

public:
  constexpr pointer_type_info(const type_info&  target) noexcept:
  m_target(&target){}

  constexpr const type_info&   get_target() const noexcept{return *m_target;}

};


class
reference_type_info: public pointer_type_info
{
public:
  constexpr reference_type_info(const type_info&  target) noexcept:
  pointer_type_info(target){}

};


}


using types::null_pointer_type_info;
using types::generic_pointer_type_info;
using types::pointer_type_info;
using types::reference_type_info;
using types::pointer_type_size;


}


#endif




