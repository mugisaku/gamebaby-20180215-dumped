#include"libgbsnd/object.hpp"
#include<new>


namespace gbsnd{
namespace devices{




value
property::
get() const noexcept
{
    switch(m_kind)
    {
  case(kind::b  ): return value(refer<bool>());
  case(kind::i8 ): return value(static_cast<int>(refer<  int8_t>()));
  case(kind::u8 ): return value(static_cast<int>(refer< uint8_t>()));
  case(kind::i16): return value(static_cast<int>(refer< int16_t>()));
  case(kind::u16): return value(static_cast<int>(refer<uint16_t>()));
  case(kind::i32): return value(static_cast<int>(refer< int32_t>()));
  case(kind::u32): return value(static_cast<int>(refer<uint32_t>()));
    }


  return value();
}


void
property::
set(const value&  v, const execution_context*  ctx) const noexcept
{
    switch(m_kind)
    {
  case(kind::b  ): refer<bool>()     = v.get_integer_value(ctx).get_integer();break;
  case(kind::i8 ): refer<  int8_t>() = v.get_integer_value(ctx).get_integer();break;
  case(kind::u8 ): refer< uint8_t>() = v.get_integer_value(ctx).get_integer();break;
  case(kind::i16): refer< int16_t>() = v.get_integer_value(ctx).get_integer();break;
  case(kind::u16): refer<uint16_t>() = v.get_integer_value(ctx).get_integer();break;
  case(kind::i32): refer< int32_t>() = v.get_integer_value(ctx).get_integer();break;
  case(kind::u32): refer<uint32_t>() = v.get_integer_value(ctx).get_integer();break;
    }


    if(m_notifier)
    {
      *m_notifier = true;
    }
}




}}




