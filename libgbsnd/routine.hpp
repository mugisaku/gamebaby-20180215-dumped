#ifndef LIBGBSND_ROUTINE_HPP
#define LIBGBSND_ROUTINE_HPP


#include"libgbstd/string.hpp"
#include<vector>


namespace gbsnd{
namespace devices{


using parameter_list = std::vector<gbstd::string>;


class block;


class
routine
{
  struct data;

  data*  m_data=nullptr;

  void  unrefer() noexcept;

public:
  routine() noexcept;
  routine(const routine&   rhs) noexcept{*this = rhs;}
  routine(      routine&&  rhs) noexcept{*this = std::move(rhs);}
 ~routine(){unrefer();}

  routine&  operator=(const routine&   rhs) noexcept;
  routine&  operator=(      routine&&  rhs) noexcept;

  const parameter_list&  get_parameter_list() const noexcept;

  const block*  get_block() const noexcept;

};


}


using devices::routine;


}




#endif




