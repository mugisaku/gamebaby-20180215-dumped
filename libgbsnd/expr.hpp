#ifndef LIBGBSND_EXPR_HPP
#define LIBGBSND_EXPR_HPP


#include"libgbsnd/object.hpp"
#include"libgbsnd/script.hpp"
#include"libgbstd/utility.hpp"
#include<memory>


namespace gbsnd{
namespace devices{


class expr;
class operand;
class unary_operation;
class binary_operation;
class execution_context;


class
expr
{
  struct data;

  data*  m_data=nullptr;

  void  unrefer() noexcept;

public:
  expr() noexcept{}
  expr(operand&&  o) noexcept{*this = std::move(o);}
  expr(unary_operation&&  unop) noexcept{*this = std::move(unop);}
  expr(binary_operation&&  binop) noexcept{*this = std::move(binop);}
  expr(const expr&   rhs) noexcept{*this = rhs;}
  expr(      expr&&  rhs) noexcept{*this = std::move(rhs);}
 ~expr(){unrefer();}

  expr&  operator=(operand&&  o) noexcept;
  expr&  operator=(unary_operation&&  unop) noexcept;
  expr&  operator=(binary_operation&&  binop) noexcept;
  expr&  operator=(const expr&   rhs) noexcept;
  expr&  operator=(      expr&&  rhs) noexcept;

  operator bool() const noexcept{return m_data;}

  bool  is_operand()          const noexcept;
  bool  is_unary_operation()  const noexcept;
  bool  is_binary_operation() const noexcept;

  operand&           get_operand()          const noexcept;
  unary_operation&   get_unary_operation()  const noexcept;
  binary_operation&  get_binary_operation() const noexcept;

  value  evaluate(const execution_context&  ctx) const noexcept;

  void  print() const noexcept;

};


class
operand
{
  enum class kind{
    null,
    undefined_literal,
    boolean_literal,
    integer_literal,
    identifier,
    expression,
  } m_kind=kind::null; 

  union data{
    bool  b;

    uint64_t  i;

    identifier  id;

    expr  e;

    data(){}
   ~data(){}

  } m_data;

public:
  operand() noexcept{}
  operand(undefined  u) noexcept{*this = u;}
  operand(bool  b) noexcept{*this = b;}
  operand(uint64_t  i) noexcept{*this = i;}
  operand(const identifier&  id) noexcept{*this = std::move(id);}
  operand(expr&&  e) noexcept{*this = std::move(e);}
  operand(const operand&   rhs) noexcept{*this = rhs;}
  operand(      operand&&  rhs) noexcept{*this = std::move(rhs);}
 ~operand(){clear();}

  operand&  operator=(undefined  u) noexcept;
  operand&  operator=(bool  b) noexcept;
  operand&  operator=(uint64_t  i) noexcept;
  operand&  operator=(const identifier&  id) noexcept;
  operand&  operator=(expr&&  e) noexcept;
  operand&  operator=(const operand&   rhs) noexcept;
  operand&  operator=(      operand&&  rhs) noexcept;


  void  clear() noexcept;

  bool  is_undefined_literal()  const noexcept{return m_kind == kind::undefined_literal;}
  bool  is_boolean_literal()  const noexcept{return m_kind == kind::boolean_literal;}
  bool  is_integer_literal()  const noexcept{return m_kind == kind::integer_literal;}
  bool  is_identifier()       const noexcept{return m_kind == kind::identifier;}
  bool  is_expression()       const noexcept{return m_kind == kind::expression;}

  bool                  get_boolean_literal()  const noexcept{return m_data.b;}
  uint64_t              get_integer_literal()  const noexcept{return m_data.i;}
  const identifier&     get_identifier()       const noexcept{return m_data.id;}
  const expr&           get_expression()       const noexcept{return m_data.e;}

  value  evaluate(const execution_context&  ctx) const noexcept;

  void  print() const noexcept;

};


class
unary_operation
{
  enum class kind{
     prefix,
    postfix,

  } m_kind;

  operator_word  m_word;

  expr  m_expr;

public:
  unary_operation() noexcept;
  unary_operation(bool  prefix, operator_word  word) noexcept: m_kind(prefix? kind::prefix:kind::postfix), m_word(word){}

  void  reset(expr&&  expr) noexcept{m_expr = std::move(expr);}

  bool  is_prefix()  const noexcept{return m_kind == kind::prefix;}
  bool  is_postfix() const noexcept{return m_kind == kind::postfix;}

  value  evaluate(const execution_context&  ctx) const noexcept;

  void  print() const noexcept;

};


class
binary_operation
{
  operator_word  m_word;

  expr   m_left_expr;
  expr  m_right_expr;

public:
  binary_operation() noexcept;
  binary_operation(operator_word  word) noexcept: m_word(word){}

  void  reset(expr&&  l, expr&&  r) noexcept;

  value  evaluate(const execution_context&  ctx) const noexcept;

  void  print() const noexcept;

};


expr  make_expr(gbstd::string_view  sv) noexcept;
expr  read_expr(script_token_cursor&  cur) noexcept;


}


using devices::expr;
using devices::make_expr;
using devices::read_expr;


}




#endif




