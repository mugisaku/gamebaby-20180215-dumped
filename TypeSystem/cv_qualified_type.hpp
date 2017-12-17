#ifndef cv_qualified_type_HPP
#define cv_qualified_type_HPP


#include<string_view>


namespace ts{
namespace types{


class type;


class
type_index
{
  uint32_t  m_value;

public:
  constexpr type_index(uint32_t  v=0) noexcept: m_value(v){}

  constexpr uint32_t  get_value() const noexcept{return m_value;}

};


class
simple_type
{
  std::string_view  m_target_name;

public:
  simple_type(const char*  name="") noexcept: m_target_name(name){}

  const type&  get_type() const noexcept;

  std::string_view  get_name() const noexcept{return m_target_name;}

};


constexpr unsigned int     const_flag = 1;
constexpr unsigned int  volatile_flag = 2;


class
cv_qualified_type: public simple_type
{
  type_index  m_type_index;

  unsigned int  m_flags=0;

public:
  cv_qualified_type(                     type_index  i) noexcept:                 m_type_index(i){}
  cv_qualified_type(unsigned int  flags, type_index  i) noexcept: m_flags(flags), m_type_index(i){}
  cv_qualified_type(                     const char*  name) noexcept:                 simple_type(name){}
  cv_qualified_type(unsigned int  flags, const char*  name) noexcept: m_flags(flags), simple_type(name){}

  const type&  get_type() const noexcept;

  bool  test_const_flag()    const noexcept{return m_flags&   const_flag;}
  bool  test_volatile_flag() const noexcept{return m_flags&volatile_flag;}

};


class   pointer_type: public cv_qualified_type{};
class reference_type: public cv_qualified_type{};
class     alias_type: public cv_qualified_type{};




}


using types::type_index;
using types::simple_type;
using types::cv_qualified_type;
using types::pointer_type;
using types::reference_type;
using types::alias_type;


}


#endif




