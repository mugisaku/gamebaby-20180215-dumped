#ifndef LIBGBSND_OBJECT_HPP
#define LIBGBSND_OBJECT_HPP


#include<cstdint>
#include<cstdio>
#include"libgbstd/string.hpp"
#include"libgbsnd/routine.hpp"


namespace gbsnd{
namespace devices{


class object;


class
reference
{
  object*  m_pointer=nullptr;

public:
  reference(object&  o) noexcept: m_pointer(&o){}

  object&  operator()() const noexcept{return *m_pointer;}

};


class
value
{
  enum class kind{
    null,
    integer,
    reference,
    routine,

  } m_kind=kind::null;

  union data{
    int        i;
    reference  r;
    routine   rt;

    data(){}
   ~data(){}

  } m_data;

public:
  value() noexcept{}
  value(int  i) noexcept{*this = i;}
  value(reference  r) noexcept{*this = r;}
  value(const routine&  rt) noexcept{*this = rt;}
  value(const value&   rhs) noexcept{*this = rhs;}
  value(      value&&  rhs) noexcept{*this = std::move(rhs);}
 ~value(){clear();}

  value&  operator=(int  i) noexcept;
  value&  operator=(reference  r) noexcept;
  value&  operator=(const routine&  rt) noexcept;
  value&  operator=(const value&   rhs) noexcept;
  value&  operator=(      value&&  rhs) noexcept;

  void  clear() noexcept;

};


class
object
{
  gbstd::string  m_name;

  value  m_value;

public:
  object() noexcept{}
  object(gbstd::string_view  name, value&&  v) noexcept: m_name(name), m_value(std::move(v)){}

  const gbstd::string&   get_name() const noexcept{return m_name;}
  const value&        get_value() const noexcept{return m_value;}

};


}


using devices::reference;
using devices::value;
using devices::object;


}




#endif




