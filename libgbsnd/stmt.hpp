#ifndef LIBGBSND_STMT_HPP
#define LIBGBSND_STMT_HPP


#include"libgbsnd/expr.hpp"
#include<vector>
#include<cstdarg>


namespace gbsnd{
namespace devices{


class stmt;
class script_token_string;




enum class
stmt_kind
{
  null,
  expression,
  label,
  sleep,
  print,
  return_,
  exit,
  jump,
  jump_if_zero,
  jump_if_not_zero,

};


class
stmt
{
  stmt_kind  m_kind=stmt_kind::null;

  expr_array  m_expr;

  gbstd::string  m_label;

public:
  stmt() noexcept{}
  stmt(expr_array&&  expr) noexcept: m_kind(stmt_kind::expression), m_expr(std::move(expr)){}
  stmt(stmt_kind  k, expr_array&&  expr) noexcept: m_kind(k), m_expr(std::move(expr)){}
  stmt(stmt_kind  k, gbstd::string_view  label) noexcept: m_kind(k), m_label(label){}
  stmt(stmt_kind  k, expr_array&&  expr, gbstd::string_view  label) noexcept: m_kind(k),
  m_expr(std::move(expr)),
  m_label(label){}

  operator bool() const noexcept{return m_kind != stmt_kind::null;}

  bool  is_expression() const noexcept{return m_kind == stmt_kind::expression;}
  bool  is_return()     const noexcept{return m_kind == stmt_kind::return_;}
  bool  is_label()      const noexcept{return m_kind == stmt_kind::label;}
  bool  is_sleep()      const noexcept{return m_kind == stmt_kind::sleep;}
  bool  is_print()      const noexcept{return m_kind == stmt_kind::print;}
  bool  is_exit()       const noexcept{return m_kind == stmt_kind::exit;}
  bool  is_jump()       const noexcept{return m_kind == stmt_kind::jump;}
  bool  is_jump_if_zero()     const noexcept{return m_kind == stmt_kind::jump_if_zero;}
  bool  is_jump_if_not_zero() const noexcept{return m_kind == stmt_kind::jump_if_not_zero;}

  const expr_array&     get_expr()  const noexcept{return m_expr;}
  const gbstd::string&  get_label() const noexcept{return m_label;}

  void  print() const noexcept;

};


using stmt_list = std::vector<stmt>;

stmt_list*  build_stmt_list(const script_token_string&  toks) noexcept;


}


using devices::stmt;


}




#endif




