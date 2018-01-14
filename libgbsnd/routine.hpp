#ifndef LIBGBSND_ROUTINE_HPP
#define LIBGBSND_ROUTINE_HPP


#include"libgbsnd/stmt.hpp"


namespace gbsnd{
namespace devices{


class
routine
{
  gbstd::string  m_name;

  block*  m_block=nullptr;

public:
  routine() noexcept{}
  routine(gbstd::string_view  name, block*  blk=nullptr) noexcept:
  m_name(name),
  m_block(blk){}
  routine(const routine&   rhs) noexcept{*this = rhs;}
  routine(      routine&&  rhs) noexcept{*this = std::move(rhs);}
 ~routine(){clear();}

  routine&  operator=(const routine&   rhs) noexcept;
  routine&  operator=(      routine&&  rhs) noexcept;

  void  clear() noexcept;

  const gbstd::string&  get_name() const noexcept{return m_name;}
  const block*  get_block() const noexcept{return m_block;}

};


}


using devices::routine;


}




#endif




