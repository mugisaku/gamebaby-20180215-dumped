#ifndef LIBGBSND_EXPR_HPP
#define LIBGBSND_EXPR_HPP


#include"libgbsnd/object.hpp"


namespace gbsnd{
namespace devices{


template<typename  T>
inline T*
duplicate(T*  src) noexcept
{
  return src? new T(*src):nullptr;
}


class expr;
class execution_context;


enum class
unary_operator
{
  null,
  neg,
  log_not,
  bit_not,
};


class
unary_operation
{
  unary_operator  m_operator=unary_operator::null;

  expr*  m_expr=nullptr;

public:
  unary_operation() noexcept;
  unary_operation(unary_operator  op, expr*  expr) noexcept{assign(op,expr);}
  unary_operation(const unary_operation&   rhs) noexcept{*this = rhs;}
  unary_operation(      unary_operation&&  rhs) noexcept{*this = std::move(rhs);}
 ~unary_operation(){clear();}

  unary_operation&  operator=(const unary_operation&   rhs) noexcept;
  unary_operation&  operator=(      unary_operation&&  rhs) noexcept;

  void  assign(unary_operator  op, expr*  expr) noexcept;

  void  clear() noexcept;

  value  evaluate(const execution_context&  ctx) const noexcept;

};


enum class
binary_operator
{
  null,
  add,
  sub,
  mul,
  div,
  rem,
  shl,
  shr,
  bit_and,
  bit_or,
  bit_xor,
  log_nd,
  log_or,
  eq,
  neq,
  lt,
  lteq,
  gt,
  gteq,
  asmt,

};

class
binary_operation
{
  binary_operator  m_operator=binary_operator::null;

  expr*   m_left_expr=nullptr;
  expr*  m_right_expr=nullptr;

public:
  binary_operation() noexcept;
  binary_operation(binary_operator  op, expr*  l, expr*  r) noexcept{assign(op,l,r);}
  binary_operation(const binary_operation&   rhs) noexcept{*this = rhs;}
  binary_operation(      binary_operation&&  rhs) noexcept{*this = std::move(rhs);}
 ~binary_operation(){clear();}

  binary_operation&  operator=(const binary_operation&   rhs) noexcept;
  binary_operation&  operator=(      binary_operation&&  rhs) noexcept;

  void  assign(binary_operator  op, expr*  l, expr*  r) noexcept;

  void  clear() noexcept;
  
  value  evaluate(const execution_context&  ctx) const noexcept;

};


class
expr
{
  enum class kind{
    null,
    integer_literal,
    identifier,
     unary_operation,
    binary_operation,

  } m_kind=kind::null;

  union data{
    unary_operation    unop;
    binary_operation  binop;

    int            i;
    gbstd::string  s;

    data(){}
   ~data(){}
  } m_data;

public:
  expr() noexcept{}
  expr(int  i) noexcept{*this = i;}
  expr(gbstd::string&&  s) noexcept{*this = std::move(s);}
  expr(unary_operation&&  unop) noexcept{*this = std::move(unop);}
  expr(binary_operation&&  binop) noexcept{*this = std::move(binop);}
  expr(const expr&   rhs) noexcept{*this = rhs;}
  expr(      expr&&  rhs) noexcept{*this = std::move(rhs);}
 ~expr(){clear();}

  expr&  operator=(int  i) noexcept;
  expr&  operator=(gbstd::string&&  s) noexcept;
  expr&  operator=(unary_operation&&  unop) noexcept;
  expr&  operator=(binary_operation&&  binop) noexcept;
  expr&  operator=(const expr&   rhs) noexcept;
  expr&  operator=(      expr&&  rhs) noexcept;

  void  clear() noexcept;

  bool  is_integer_literal()  const noexcept{return m_kind == kind::integer_literal;}
  bool  is_identifier()       const noexcept{return m_kind == kind::identifier;}
  bool  is_unary_operation()  const noexcept{return m_kind == kind::unary_operation;}
  bool  is_binary_operation() const noexcept{return m_kind == kind::binary_operation;}

  int                      get_integer_literal()  const noexcept{return m_data.i;}
  const gbstd::string&     get_identifier()       const noexcept{return m_data.s;}
  const unary_operation&   get_unary_operation()  const noexcept{return m_data.unop;}
  const binary_operation&  get_binary_operation() const noexcept{return m_data.binop;}

  value  evaluate(const execution_context&  ctx) const noexcept;

};


}


using devices::expr;


}




#endif




