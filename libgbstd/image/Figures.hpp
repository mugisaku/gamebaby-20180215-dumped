#ifndef GMBB_Figures_HPP
#define GMBB_Figures_HPP


#include<cstdio>


#ifndef report
#define report printf("[report] %s, %s, %d\n",__FILE__,__func__,__LINE__);
#endif


namespace gbstd{
namespace images{


class
point
{
  int  m_x;
  int  m_y;

public:
  constexpr point(int  x=0, int  y=0) noexcept:
  m_x(x),
  m_y(y){}


  constexpr int  get_x() const noexcept{return m_x;}
  constexpr int  get_y() const noexcept{return m_y;}

  void  set_x(int  v) noexcept{m_x = v;}
  void  set_y(int  v) noexcept{m_y = v;}

  constexpr point  operator+(point const&  rhs) const noexcept
  {
    return point(m_x+rhs.m_x,m_y+rhs.m_y);
  }

  constexpr point  operator-(point const&  rhs) const noexcept
  {
    return point(m_x-rhs.m_x,m_y-rhs.m_y);
  }

  constexpr point  operator+(int  n) const noexcept
  {
    return point(m_x+n,m_y+n);
  }

  constexpr point  operator*(int  n) const noexcept
  {
    return point(m_x*n,m_y*n);
  }

  constexpr point  operator/(int  n) const noexcept
  {
    return point(m_x/n,m_y/n);
  }

  constexpr point  operator%(int  n) const noexcept
  {
    return point(m_x%n,m_y%n);
  }

  constexpr point  operator-() const noexcept
  {
    return point(-m_x,-m_y);
  }

  constexpr point&  operator+=(point const&  rhs) noexcept
  {
    m_x += rhs.m_x;
    m_y += rhs.m_y;

    return *this;
  }

  constexpr point&  operator*=(int  n) noexcept
  {
    m_x *= n;
    m_y *= n;

    return *this;
  }

  constexpr point&  operator/=(int  n) noexcept
  {
    m_x /= n;
    m_y /= n;

    return *this;
  }

  constexpr point&  operator%=(int  n) noexcept
  {
    m_x %= n;
    m_y %= n;

    return *this;
  }

  void  print(char const*  prefix="") const
  {
    printf("[print point %s] %4d %4d\n",prefix,m_x,m_y);
  }


  point&  move_x(int  n) noexcept
  {
    m_x += n;

    return *this;
  }


  point&  move_y(int  n) noexcept
  {
    m_y += n;

    return *this;
  }


  void  transform(int  w, int  h) noexcept
  {
      if(m_x < 0)
      {
          while(m_x < 0)
          {
            m_x += w;
          }
      }

    else
      if(m_x >= w)
      {
          while(m_x >= w)
          {
            m_x -= w;
          }
      }


      if(m_y < 0)
      {
          while(m_y < 0)
          {
            m_y += h;
          }
      }

    else
      if(m_y >= h)
      {
          while(m_y >= h)
          {
            m_y -= h;
          }
      }
  }


  void  transform(int  w, int  h, int  field_w, int  field_h) noexcept
  {
      while((m_x+w) >= field_w)
      {
        m_x -= field_w;
      }


      while((m_y+h) >= field_h)
      {
        m_y -= field_h;
      }
  }

};


class
rectangle: public point
{
  int  m_w;
  int  m_h;

public:
  constexpr rectangle(int  x=0, int  y=0, int  w=0, int  h=0) noexcept:
  point(x,y),
  m_w(w),
  m_h(h){}

  constexpr int  get_w() const noexcept{return m_w;}
  constexpr int  get_h() const noexcept{return m_h;}

  void  set_w(int  v) noexcept{m_w = v;}
  void  set_h(int  v) noexcept{m_h = v;}

};


class
triangle
{
  point  m_a;
  point  m_b;
  point  m_c;

public:
  constexpr triangle(point  a=point(), point  b=point(), point  c=point()) noexcept:
  m_a(a),
  m_b(b),
  m_c(c){}

};


class
line
{
  point  m_a;
  point  m_b;

public:
  constexpr line(point  a=point(), point  b=point()) noexcept:
  m_a(a),
  m_b(b){}

};


}}


#endif




