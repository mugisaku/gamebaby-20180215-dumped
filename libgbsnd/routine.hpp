#ifndef LIBGBSND_ROUTINE_HPP
#define LIBGBSND_ROUTINE_HPP


#include"libgbstd/string.hpp"
#include"libgbsnd/stmt.hpp"
#include<vector>
#include<memory>


namespace gbsnd{
namespace devices{


using parameter_list = std::vector<gbstd::string>;

class script_token_string;


class
routine
{
  parameter_list  m_parameter_list;

  std::unique_ptr<stmt_list>  m_stmt_list;

public:
  routine() noexcept{}
  routine(const script_token_string&  parals_src, const script_token_string&  blk_src) noexcept;
  routine(const routine&   rhs) noexcept{*this = rhs;}
  routine(      routine&&  rhs) noexcept{*this = std::move(rhs);}

  routine&  operator=(const routine&   rhs) noexcept;
  routine&  operator=(      routine&&  rhs) noexcept;

  void                   set_parameter_list(parameter_list&&  ls)       noexcept;
  const parameter_list&  get_parameter_list(                    ) const noexcept;

  void                               set_stmt_list(stmt_list*  ls)       noexcept;
  const std::unique_ptr<stmt_list>&  get_stmt_list(              ) const noexcept;

  void  print() const noexcept;

};


}


using devices::routine;


}




#endif




