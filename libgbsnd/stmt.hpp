#ifndef LIBGBSND_STMT_HPP
#define LIBGBSND_STMT_HPP


#include"libgbsnd/expr.hpp"
#include<vector>


namespace gbsnd{
namespace devices{


class stmt;
class script_token_string;


class
block
{
  block*  m_parent=nullptr;

  bool  m_repetition=false;

  std::vector<stmt>  m_stmt_list;

public:
  block() noexcept{}
  block(const script_token_string&  toks) noexcept;

  const stmt*  begin() const noexcept;
  const stmt*    end() const noexcept;

};


class    break_stmt{public: constexpr    break_stmt() noexcept{}};
class continue_stmt{public: constexpr continue_stmt() noexcept{}};
class  default_stmt{public: constexpr  default_stmt() noexcept{}};


class
case_stmt
{
  int  m_value;

public:
  constexpr case_stmt(int  v) noexcept: m_value(v){}

  constexpr int  get_value() const noexcept{return m_value;}

};


class
label_stmt
{
  gbstd::string  m_text;

public:
  label_stmt(gbstd::string_view text) noexcept: m_text(text){}

  const gbstd::string&  get_text() const noexcept{return m_text;}

};


class
for_stmt: public block
{
  expr  m_initialize_expr;
  expr   m_condition_expr;
  expr      m_modify_expr;

public:

};


struct
return_stmt
{
  devices::expr  expr;

};


class
stmt
{
  enum class kind{
    null,
    expression,
    label,
    block,
    if_,
    while_,
    for_,
    break_,
    continue_,
    goto_,
    switch_,
    case_,
    default_,
    return_,

  } m_kind=kind::null;

  union data{
    expr           e;
    block        blk;
    label_stmt   lbl;
    return_stmt  ret;
    case_stmt    cas;

    data(){}
   ~data(){}

  } m_data;

public:
  stmt() noexcept{}
  stmt(expr&&  e) noexcept{*this = std::move(e);}
  stmt(block&&          blk) noexcept{*this = std::move(blk);}
  stmt(label_stmt&&     lbl) noexcept{*this = std::move(lbl);}
  stmt(return_stmt&&    ret) noexcept{*this = std::move(ret);}
  stmt(break_stmt     brk) noexcept{*this = brk;}
  stmt(continue_stmt  cnt) noexcept{*this = cnt;}
  stmt(default_stmt   dfl) noexcept{*this = dfl;}
  stmt(case_stmt      cas) noexcept{*this = cas;}
  stmt(const stmt&   rhs) noexcept{*this = rhs;}
  stmt(      stmt&&  rhs) noexcept{*this = std::move(rhs);}
 ~stmt(){clear();}

  stmt&  operator=(expr&&  e) noexcept;
  stmt&  operator=(block&&  blk) noexcept;
  stmt&  operator=(label_stmt&&   lbl) noexcept;
  stmt&  operator=(return_stmt&&  ret) noexcept;
  stmt&  operator=(break_stmt     brk) noexcept;
  stmt&  operator=(continue_stmt  cnt) noexcept;
  stmt&  operator=(default_stmt   dfl) noexcept;
  stmt&  operator=(case_stmt      cas) noexcept;
  stmt&  operator=(const stmt&   rhs) noexcept;
  stmt&  operator=(      stmt&&  rhs) noexcept;

  operator bool() const noexcept{return m_kind != kind::null;}

  void  clear() noexcept;

  bool  is_expression() const noexcept{return m_kind == kind::expression;}
  bool  is_return()     const noexcept{return m_kind == kind::return_;}
  bool  is_if()         const noexcept{return m_kind == kind::if_;}
  bool  is_while()      const noexcept{return m_kind == kind::while_;}
  bool  is_for()        const noexcept{return m_kind == kind::for_;}
  bool  is_label()      const noexcept{return m_kind ==  kind::label;}
  bool  is_block()      const noexcept{return m_kind ==  kind::block;}
  bool  is_break()      const noexcept{return m_kind ==  kind::break_;}
  bool  is_continue()   const noexcept{return m_kind ==  kind::continue_;}
  bool  is_goto()       const noexcept{return m_kind ==  kind::goto_;}
  bool  is_case()       const noexcept{return m_kind ==  kind::case_;}
  bool  is_switch()     const noexcept{return m_kind ==  kind::switch_;}
  bool  is_default()    const noexcept{return m_kind ==  kind::default_;}

  const expr&         get_expr()   const noexcept{return m_data.e;}
  const label_stmt&   get_label()  const noexcept{return m_data.lbl;}
  const return_stmt&  get_return() const noexcept{return m_data.ret;}
  const case_stmt&    get_case()   const noexcept{return m_data.cas;}
  const block&        get_block()  const noexcept{return m_data.blk;}

};


}


using devices::stmt;
using devices::block;
using devices::break_stmt;
using devices::continue_stmt;
using devices::default_stmt;
using devices::case_stmt;
using devices::return_stmt;
using devices::label_stmt;


}




#endif




