#ifndef cv_qualified_type_HPP
#define cv_qualified_type_HPP


#include<string_view>
#include<memory>


namespace ts{
namespace types{


class type;


class
cv_qualified_type
{
  std::string_view  m_target_name;

  std::unique_ptr<type>  m_target_type;

  bool  m_const_flag;
  bool  m_volatile_flag;

public:
  cv_qualified_type() noexcept{}

  const type&  get_type() const noexcept;

  bool  test_const_flag() const noexcept{return m_const_flag;}
  bool  test_volatile_flag() const noexcept{return m_volatile_flag;}

};


class   pointer_type: public cv_qualified_type{};
class reference_type: public cv_qualified_type{};
class     alias_type: public cv_qualified_type{};




}


using types::cv_qualified_type;
using types::pointer_type;
using types::reference_type;
using types::alias_type;


}


#endif




