#ifndef LIBGBSND_STMT_HPP
#define LIBGBSND_STMT_HPP


#include"libgbsnd/expr.hpp"
#include<vector>
#include<cstdarg>


namespace gbsnd{
namespace devices{


class stmt;
class script_token_string;


class
sleep_stmt
{
  expr_array  m_expr;

public:
  sleep_stmt(expr_array&&  e) noexcept: m_expr(std::move(e)){}

  const expr_array&  get_expr() const noexcept{return m_expr;}

};


class
label_stmt
{
  gbstd::string  m_text;

public:
  explicit label_stmt(gbstd::string_view  text) noexcept: m_text(text){}

  const gbstd::string&  get_text() const noexcept{return m_text;}

};


class
return_stmt
{
  expr_array  m_expr;

public:
  return_stmt() noexcept{}
  return_stmt(expr_array&&  expr) noexcept:
  m_expr(std::move(expr)){}

  const expr_array&  get_expr() const noexcept{return m_expr;}

};


class
exit_stmt
{
  expr_array  m_expr;

public:
  exit_stmt() noexcept{}
  exit_stmt(expr_array&&  expr) noexcept:
  m_expr(std::move(expr)){}

  const expr_array&  get_expr() const noexcept{return m_expr;}

};


class
print_stmt
{
  expr_array  m_expr;

public:
  print_stmt(expr_array&&  expr) noexcept:
  m_expr(std::move(expr)){}

  const expr_array&  get_expr() const noexcept{return m_expr;}

};


class
branch_stmt
{
  expr_array  m_expr;

  gbstd::string  m_dst_label;

  bool  m_boolean;

public:
  branch_stmt(expr_array&&  expr, gbstd::string_view  dst_label, bool  boolean) noexcept:
  m_expr(std::move(expr)),
  m_dst_label(dst_label),
  m_boolean(boolean){}

  const expr_array&  get_expr() const noexcept{return m_expr;}

  const gbstd::string&  get_dst_label() const noexcept{return m_dst_label;}

  bool  get_boolean() const noexcept{return m_boolean;}

};


class
jump_stmt
{
  gbstd::string  m_dst_label;

public:
  jump_stmt(gbstd::string_view  dst_label) noexcept:
  m_dst_label(dst_label){}

  const gbstd::string&  get_dst_label() const noexcept{return m_dst_label;}

};


class
stmt
{
  enum class kind{
    null,
    expression,
    label,
    sleep,
    print,
    return_,
    exit,
    branch,
    jump,

  } m_kind=kind::null;

  union data{
    expr_array  e;

    label_stmt   lbl;
    return_stmt  ret;
    sleep_stmt   slp;
    print_stmt   prn;
    exit_stmt    exi;
    branch_stmt  bra;
    jump_stmt    jmp;

    data(){}
   ~data(){}

  } m_data;

public:
  stmt() noexcept{}
  stmt(expr_array&&  e) noexcept{*this = std::move(e);}
  stmt(label_stmt&&     lbl) noexcept{*this = std::move(lbl);}
  stmt(return_stmt&&    ret) noexcept{*this = std::move(ret);}
  stmt(sleep_stmt&&   slp) noexcept{*this = std::move(slp);}
  stmt(print_stmt&&   prn) noexcept{*this = std::move(prn);}
  stmt(exit_stmt&&    exi) noexcept{*this = std::move(exi);}
  stmt(branch_stmt&&  bra) noexcept{*this = std::move(bra);}
  stmt(jump_stmt&&    jmp) noexcept{*this = std::move(jmp);}
  stmt(const stmt&   rhs) noexcept{*this = rhs;}
  stmt(      stmt&&  rhs) noexcept{*this = std::move(rhs);}
 ~stmt(){clear();}

  stmt&  operator=(expr_array&&  e) noexcept;
  stmt&  operator=(label_stmt&&   lbl) noexcept;
  stmt&  operator=(return_stmt&&  ret) noexcept;
  stmt&  operator=(sleep_stmt&&   slp) noexcept;
  stmt&  operator=(print_stmt&&   prn) noexcept;
  stmt&  operator=(exit_stmt&&    exi) noexcept;
  stmt&  operator=(branch_stmt&&  bra) noexcept;
  stmt&  operator=(jump_stmt&&    jmp) noexcept;
  stmt&  operator=(const stmt&   rhs) noexcept;
  stmt&  operator=(      stmt&&  rhs) noexcept;

  operator bool() const noexcept{return m_kind != kind::null;}

  void  clear() noexcept;

  bool  is_expression() const noexcept{return m_kind == kind::expression;}
  bool  is_return()     const noexcept{return m_kind == kind::return_;}
  bool  is_label()      const noexcept{return m_kind ==  kind::label;}
  bool  is_sleep()      const noexcept{return m_kind ==  kind::sleep;}
  bool  is_print()      const noexcept{return m_kind ==  kind::print;}
  bool  is_exit()       const noexcept{return m_kind ==  kind::exit;}
  bool  is_branch()     const noexcept{return m_kind ==  kind::branch;}
  bool  is_jump()       const noexcept{return m_kind ==  kind::jump;}

  const expr_array&   get_expr()   const noexcept{return m_data.e;}
  const label_stmt&   get_label()  const noexcept{return m_data.lbl;}
  const return_stmt&  get_return() const noexcept{return m_data.ret;}
  const sleep_stmt&   get_sleep()  const noexcept{return m_data.slp;}
  const print_stmt&   get_print()  const noexcept{return m_data.prn;}
  const exit_stmt&    get_exit()   const noexcept{return m_data.exi;}
  const branch_stmt&  get_branch() const noexcept{return m_data.bra;}
  const jump_stmt&    get_jump()   const noexcept{return m_data.jmp;}

  void  print() const noexcept;

};


using stmt_list = std::vector<stmt>;

stmt_list*  build_stmt_list(const script_token_string&  toks) noexcept;


}


using devices::stmt;
using devices::return_stmt;
using devices::label_stmt;
using devices::sleep_stmt;


}




#endif




