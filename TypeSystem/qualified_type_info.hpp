#ifndef qualified_type_info_HPP
#define qualified_type_info_HPP


namespace ts{
namespace types{


class type_info;


class
qualified_type_info
{
  const type_info*  m_target;

public:
  constexpr qualified_type_info(const type_info&  target) noexcept:
  m_target(&target){}

  constexpr const type_info&   get_target() const noexcept{return *m_target;}

};


class
const_qualified_type_info: public qualified_type_info
{
public:
  constexpr const_qualified_type_info(const type_info&  target) noexcept:
  qualified_type_info(target){}

};


class
volatile_qualified_type_info: public qualified_type_info
{
public:
  constexpr volatile_qualified_type_info(const type_info&  target) noexcept:
  qualified_type_info(target){}

};


class
const_volatile_qualified_type_info: public qualified_type_info
{
public:
  constexpr const_volatile_qualified_type_info(const type_info&  target) noexcept:
  qualified_type_info(target){}

};


}


using types::qualified_type_info;
using types::const_qualified_type_info;
using types::volatile_qualified_type_info;
using types::const_volatile_qualified_type_info;


}


#endif




