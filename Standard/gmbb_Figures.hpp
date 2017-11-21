#ifndef GMBB_Figures_HPP
#define GMBB_Figures_HPP


#include<cstdio>


#ifndef report
#define report printf("[report] %s, %s, %d\n",__FILE__,__func__,__LINE__);
#endif


namespace gmbb{


struct
Point
{
  int  x;
  int  y;

  constexpr Point(int  x=0, int  y=0) noexcept:
  x(x), y(y){}


  constexpr Point  operator+(Point const&  rhs) const noexcept
  {
    return Point(x+rhs.x,y+rhs.y);
  }

  constexpr Point  operator-(Point const&  rhs) const noexcept
  {
    return Point(x-rhs.x,y-rhs.y);
  }

  constexpr Point  operator+(int  n) const noexcept
  {
    return Point(x+n,y+n);
  }

  constexpr Point  operator*(int  n) const noexcept
  {
    return Point(x*n,y*n);
  }

  constexpr Point  operator/(int  n) const noexcept
  {
    return Point(x/n,y/n);
  }

  constexpr Point  operator%(int  n) const noexcept
  {
    return Point(x%n,y%n);
  }

  constexpr Point  operator-() const noexcept
  {
    return Point(-x,-y);
  }

  constexpr Point&  operator+=(Point const&  rhs) noexcept
  {
    x += rhs.x;
    y += rhs.y;

    return *this;
  }

  constexpr Point&  operator*=(int  n) noexcept
  {
    x *= n;
    y *= n;

    return *this;
  }

  constexpr Point&  operator/=(int  n) noexcept
  {
    x /= n;
    y /= n;

    return *this;
  }

  constexpr Point&  operator%=(int  n) noexcept
  {
    x %= n;
    y %= n;

    return *this;
  }

  void  print(char const*  prefix="") const
  {
    printf("[print point %s] %4d %4d\n",prefix,x,y);
  }


  Point&  move_x(int  n) noexcept
  {
    x += n;

    return *this;
  }


  Point&  move_y(int  n) noexcept
  {
    y += n;

    return *this;
  }


  void  transform(int  w, int  h) noexcept
  {
      if(x < 0)
      {
          while(x < 0)
          {
            x += w;
          }
      }

    else
      if(x >= w)
      {
          while(x >= w)
          {
            x -= w;
          }
      }


      if(y < 0)
      {
          while(y < 0)
          {
            y += h;
          }
      }

    else
      if(y >= h)
      {
          while(y >= h)
          {
            y -= h;
          }
      }
  }


  void  transform(int  w, int  h, int  field_w, int  field_h) noexcept
  {
      while((x+w) >= field_w)
      {
        x -= field_w;
      }


      while((y+h) >= field_h)
      {
        y -= field_h;
      }
  }

};


struct
Rectangle: public Point
{
  int  w;
  int  h;

  constexpr Rectangle(int  x_=0, int  y_=0, int  w_=0, int  h_=0) noexcept:
  Point(x_,y_),
  w(w_),
  h(h_){}

};


struct
Triangle
{
  Point  a;
  Point  b;
  Point  c;

  constexpr Triangle(Point  a_=Point(), Point  b_=Point(), Point  c_=Point()) noexcept:
  a(a_), b(b_), c(c_){}

};


struct
Line
{
  Point  a;
  Point  b;

  constexpr Line(Point  a_=Point(), Point  b_=Point()) noexcept:
  a(a_), b(b_){}

};


}


#endif




