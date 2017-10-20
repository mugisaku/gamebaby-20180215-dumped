#ifndef game_Trap_HPP
#define game_Trap_HPP




namespace gmbb{


enum class
TrapKind
{
  null,
  
};


class
Trap
{
  char const*  name="";

  TrapKind  kind=TrapKind::null;

  int  value=0;

public:
  Trap() noexcept{}

  operator bool() const noexcept{return kind != TrapKind::null;}

  bool  operator==(TrapKind  k) const noexcept{return kind == k;}

  char const*  get_name() const noexcept{return name;}

  TrapKind  get_kind()  const noexcept{return kind;}

  void  set_value(int  v)       noexcept{       value = v;}
  int   get_value(      ) const noexcept{return value    ;}

};


}




#endif




