#ifndef gmbb_FixedPointNumber_HPP
#define gmbb_FixedPointNumber_HPP


#include<cstdint>


namespace gmbb{


class
fixed_point_number
{
public:
  using Type = fixed_point_number;

  struct RawValue{int32_t  data;  constexpr explicit RawValue(int32_t  dat=0) noexcept: data(dat){}};

  static constexpr int  shift_amount = 16;

  static constexpr int  unit = 1<<shift_amount;
  static constexpr int  half = unit/2;

private:
  int32_t  m_value;

  static constexpr int32_t  add_char(char  c, int32_t  n) noexcept
  {
    return ((c >= '0') && (c <= '9'))? (n*10)+(c-'0')
          : n;
  }

  static constexpr int32_t  add_char_fract(char  c, int32_t  n, int  base) noexcept
  {
    return ((c >= '0') && (c <= '9'))? n+(base*(c-'0'))
          : n;
  }

  static constexpr int32_t  to_fract_int(char const*  s, int32_t  n, int  base=(1<<shift_amount)/10) noexcept
  {
    return *s? to_fract_int(s+1,add_char_fract(*s,n,base),base/10)
          :n;
  }

  static constexpr int32_t  to_int(char const*  s, int32_t  n) noexcept
  {
    return *s? (*s == '.')? (n<<shift_amount)|to_fract_int(s+1,             0)
              :                                     to_int(s+1,add_char(*s,n))
          :(n<<shift_amount);
  }

  static constexpr int32_t  to_int(char const*  s) noexcept
  {
    return (*s == '-')? -to_int(s+1,0):to_int(s,0);
  }

public:
  constexpr explicit fixed_point_number(int  n=0) noexcept: m_value(n<<shift_amount){}
  constexpr explicit fixed_point_number(char const*  s) noexcept: m_value(to_int(s)){}
  constexpr explicit fixed_point_number(RawValue  v) noexcept: m_value(v.data){}

  Type&  operator=(int  n) noexcept{return *this = Type(n);}
  Type&  operator=(RawValue  v) noexcept{return *this = Type(v);}

  constexpr  operator bool() const noexcept{return m_value;}

  constexpr bool  operator==(Type const&  rhs) const noexcept{return m_value == rhs.m_value;}
  constexpr bool  operator!=(Type const&  rhs) const noexcept{return m_value != rhs.m_value;}
  constexpr bool  operator< (Type const&  rhs) const noexcept{return m_value <  rhs.m_value;}
  constexpr bool  operator<=(Type const&  rhs) const noexcept{return m_value <= rhs.m_value;}
  constexpr bool  operator> (Type const&  rhs) const noexcept{return m_value >  rhs.m_value;}
  constexpr bool  operator>=(Type const&  rhs) const noexcept{return m_value >= rhs.m_value;}

  constexpr Type  operator+(Type const&  rhs) const noexcept{return Type(RawValue(m_value+rhs.m_value));}
  constexpr Type  operator-(Type const&  rhs) const noexcept{return Type(RawValue(m_value-rhs.m_value));}
  constexpr Type  operator*(int  n) const noexcept{return Type(RawValue(m_value*n));}
  constexpr Type  operator/(int  n) const noexcept{return Type(RawValue(m_value/n));}
  constexpr Type  operator%(int  n) const noexcept{return Type(RawValue(m_value%n));}

  constexpr Type  round() const noexcept{return Type(RawValue((m_value+half)&0xFFFF0000));}

  Type&  operator+=(Type const&  rhs) noexcept{m_value += rhs.m_value;  return *this;}
  Type&  operator-=(Type const&  rhs) noexcept{m_value -= rhs.m_value;  return *this;}
  Type&  operator*=(int  n) noexcept{m_value *= n;  return *this;}
  Type&  operator/=(int  n) noexcept{m_value /= n;  return *this;}
  Type&  operator%=(int  n) noexcept{m_value %= n;  return *this;}

  int32_t  operator*() const noexcept{return m_value>>shift_amount;}


  RawValue  get_raw_value() const noexcept{return RawValue(m_value);}

};


using fpn = fixed_point_number;


}




#endif




