#ifndef LIBGBSND_OBJECT_HPP
#define LIBGBSND_OBJECT_HPP


#include<cstdint>
#include<cstdio>
#include"libgbstd/string.hpp"
#include"libgbsnd/routine.hpp"
#include"libgbsnd/device.hpp"


namespace gbsnd{
namespace devices{


class object;
class value;


class
property
{
public:
  using getter = value  (*)(object&  obj                 );
  using setter = void   (*)(object&  obj, const value&  v);

private:
  object*  m_object;

  getter  m_getter;
  setter  m_setter;

public:
  property(object&  obj, getter  get, setter  set) noexcept:
  m_object(&obj),
  m_getter(get),
  m_setter(set){}

  value  get(               ) const noexcept;
  void   set(const value&  v) const noexcept;

};


class
reference
{
  object*  m_pointer=nullptr;

public:
  reference(object&  o) noexcept: m_pointer(&o){}

  object&  operator()() const noexcept{return *m_pointer;}

};


class undefined{public: constexpr undefined() noexcept{}};


class
value
{
  enum class kind{
    null,
    undefined,
    boolean,
    integer,
    reference,
    routine,
    property,
    square_wave,

  } m_kind=kind::null;

  union data{
    bool             b;
    int              i;
    reference        r;
    const routine*  rt;
    property        pr;
    square_wave*    sq;

    data(){}
   ~data(){}

  } m_data;

public:
  value() noexcept{}
  value(undefined  u) noexcept{*this = u;}
  value(bool  b) noexcept{*this = b;}
  value(int  i) noexcept{*this = i;}
  value(reference  r) noexcept{*this = r;}
  value(const routine&  rt) noexcept{*this = rt;}
  value(const property&  pr) noexcept{*this = pr;}
  value(square_wave&  sq) noexcept{*this = sq;}
  value(const value&   rhs) noexcept{*this = rhs;}
  value(      value&&  rhs) noexcept{*this = std::move(rhs);}
 ~value(){clear();}

  value&  operator=(undefined  u) noexcept;
  value&  operator=(bool  b) noexcept;
  value&  operator=(int  i) noexcept;
  value&  operator=(reference  r) noexcept;
  value&  operator=(const routine&  rt) noexcept;
  value&  operator=(const property&  pr) noexcept;
  value&  operator=(square_wave&  sq) noexcept;
  value&  operator=(const value&   rhs) noexcept;
  value&  operator=(      value&&  rhs) noexcept;

  operator bool() const noexcept{return (m_kind != kind::null) && !is_undefined();}

  void  clear() noexcept;

  bool  is_undefined()   const noexcept{return m_kind == kind::undefined;}
  bool  is_boolean()     const noexcept{return m_kind == kind::boolean;}
  bool  is_reference()   const noexcept{return m_kind == kind::reference;}
  bool  is_integer()     const noexcept{return m_kind == kind::integer;}
  bool  is_routine()     const noexcept{return m_kind == kind::routine;}
  bool  is_property()    const noexcept{return m_kind == kind::property;}
  bool  is_square_wave() const noexcept{return m_kind == kind::square_wave;}

  int              get_integer()     const noexcept{return m_data.i;}
  bool             get_boolean()     const noexcept{return m_data.b;}
  reference        get_reference()   const noexcept{return m_data.r;}
  const routine&   get_routine()     const noexcept{return *m_data.rt;}
  const property&  get_property()    const noexcept{return m_data.pr;}
  square_wave&     get_square_wave() const noexcept{return *m_data.sq;}

  value  convert_to_integer() const noexcept;
  value  convert_to_boolean() const noexcept;
  value  convert_to_routine() const noexcept;

  void  print() const noexcept;

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




