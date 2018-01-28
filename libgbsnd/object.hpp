#ifndef LIBGBSND_OBJECT_HPP
#define LIBGBSND_OBJECT_HPP


#include<cstdint>
#include<cstdio>
#include"libgbstd/string.hpp"
#include"libgbsnd/routine.hpp"
#include"libgbsnd/shared_string.hpp"


namespace gbsnd{
namespace devices{


class object;
class value;
class square_wave;
class execution_context;


class
property
{
  enum class kind{
    null,
    b,
    i8,
    u8,
    i16,
    u16,
    i32,
    u32,

  } m_kind=kind::null;


  void*  m_pointer=nullptr;

  bool*  m_notifier=nullptr;

  template<typename  T>
  T&  refer() const noexcept{return *static_cast<T*>(m_pointer);}

public:
  constexpr property(    bool&  v, bool*  n=nullptr) noexcept: m_kind(kind::b  ), m_pointer(&v), m_notifier(n){}
  constexpr property(  int8_t&  v, bool*  n=nullptr) noexcept: m_kind(kind::i8 ), m_pointer(&v), m_notifier(n){}
  constexpr property( uint8_t&  v, bool*  n=nullptr) noexcept: m_kind(kind::u8 ), m_pointer(&v), m_notifier(n){}
  constexpr property( int16_t&  v, bool*  n=nullptr) noexcept: m_kind(kind::i16), m_pointer(&v), m_notifier(n){}
  constexpr property(uint16_t&  v, bool*  n=nullptr) noexcept: m_kind(kind::u16), m_pointer(&v), m_notifier(n){}
  constexpr property( int32_t&  v, bool*  n=nullptr) noexcept: m_kind(kind::i32), m_pointer(&v), m_notifier(n){}
  constexpr property(uint32_t&  v, bool*  n=nullptr) noexcept: m_kind(kind::u32), m_pointer(&v), m_notifier(n){}

  value  get(                                              ) const noexcept;
  void   set(const value&  v, const execution_context*  ctx) const noexcept;

};


class
reference
{
  object*  m_pointer=nullptr;

public:
  reference(object&  o) noexcept: m_pointer(&o){}

  object&  operator()() const noexcept{return *m_pointer;}

  property  get_property(const identifier&  id) const noexcept;

};


class
value
{
  enum class kind{
    null,
    integer,
    identifier,
    reference,
    routine,
    property,
    square_wave,

  } m_kind=kind::null;

  union data{
    int              i;
    reference        r;
    const routine*  rt;
    identifier      id;
    property        pr;
    square_wave*    sq;

    data(){}
   ~data(){}

  } m_data;

public:
  value() noexcept{}
  value(bool  b) noexcept{*this = b;}
  value(int  i) noexcept{*this = i;}
  value(reference  r) noexcept{*this = r;}
  value(const routine&  rt) noexcept{*this = rt;}
  value(const identifier&  id) noexcept{*this = id;}
  value(const property&  pr) noexcept{*this = pr;}
  value(square_wave&  sq) noexcept{*this = sq;}
  value(const value&   rhs) noexcept{*this = rhs;}
  value(      value&&  rhs) noexcept{*this = std::move(rhs);}
 ~value(){clear();}

  value&  operator=(bool  b) noexcept;
  value&  operator=(int  i) noexcept;
  value&  operator=(reference  r) noexcept;
  value&  operator=(const routine&  rt) noexcept;
  value&  operator=(const identifier&  id) noexcept;
  value&  operator=(const property&  pr) noexcept;
  value&  operator=(square_wave&  sq) noexcept;
  value&  operator=(const value&   rhs) noexcept;
  value&  operator=(      value&&  rhs) noexcept;

  operator bool() const noexcept{return m_kind != kind::null;}

  void  clear() noexcept;

  bool  is_reference()   const noexcept{return m_kind == kind::reference;}
  bool  is_integer()     const noexcept{return m_kind == kind::integer;}
  bool  is_routine()     const noexcept{return m_kind == kind::routine;}
  bool  is_identifier()  const noexcept{return m_kind == kind::identifier;}
  bool  is_property()    const noexcept{return m_kind == kind::property;}
  bool  is_square_wave() const noexcept{return m_kind == kind::square_wave;}

  int                get_integer()     const noexcept{return m_data.i;}
  reference          get_reference()   const noexcept{return m_data.r;}
  const routine&     get_routine()     const noexcept{return *m_data.rt;}
  const identifier&  get_identifier()  const noexcept{return m_data.id;}
  const property&    get_property()    const noexcept{return m_data.pr;}
  square_wave&       get_square_wave() const noexcept{return *m_data.sq;}

  value  get_integer_value(const execution_context*  ctx) const noexcept;
  value  get_routine_value(const execution_context*  ctx) const noexcept;
  value  get_reference_value(const execution_context*  ctx) const noexcept;

  void  print() const noexcept;

};


class
object: public value
{
  gbstd::string  m_name;

public:
  using value::value;

  void                   set_name(gbstd::string_view  name)       noexcept{m_name = name;}
  const gbstd::string&   get_name(                        ) const noexcept{return m_name;}

  void  print() const noexcept
  {
    printf("%s = ",m_name.data());

    value::print();
  }

};


}


using devices::reference;
using devices::value;
using devices::object;
using devices::property;


}




#endif




