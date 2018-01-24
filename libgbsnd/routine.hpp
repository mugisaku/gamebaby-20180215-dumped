#ifndef LIBGBSND_ROUTINE_HPP
#define LIBGBSND_ROUTINE_HPP


#include"libgbstd/string.hpp"
#include<vector>


namespace gbsnd{
namespace devices{


using parameter_list = std::vector<gbstd::string>;


class block;


class script_token_string;


class
routine
{
  parameter_list  m_parameter_list;

  block*  m_block=nullptr;

public:
  routine() noexcept{}
  routine(const script_token_string&  parals_src, const script_token_string&  blk_src) noexcept;
  routine(const routine&   rhs) noexcept{*this = rhs;}
  routine(      routine&&  rhs) noexcept{*this = std::move(rhs);}
 ~routine(){clear();}

  routine&  operator=(const routine&   rhs) noexcept;
  routine&  operator=(      routine&&  rhs) noexcept;

  void  clear() noexcept;

  void                   set_parameter_list(parameter_list&&  ls)       noexcept;
  const parameter_list&  get_parameter_list(                    ) const noexcept;

  void          set_block(block*  blk)       noexcept;
  const block*  get_block(           ) const noexcept;

  void  print() const noexcept;

};


}


using devices::routine;


}




#endif




