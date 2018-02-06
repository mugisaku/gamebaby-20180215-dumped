#ifndef LIBGBSND_EXPR_HPP
#define LIBGBSND_EXPR_HPP


#include"libgbsnd/object.hpp"
#include"libgbsnd/script.hpp"
#include"libgbstd/utility.hpp"
#include<memory>


namespace gbsnd{
namespace devices{


class operand;
class execution_context;
class expr_element;
class expr_array;
class data_stack;




struct
prefix_unary_operator
{
  operator_word  word;

};


struct
postfix_unary_operator
{
  operator_word  word;

};


struct
binary_operator
{
  operator_word  word;

};


class
operation
{
  struct data;

  data*  m_data=nullptr;

  void  unrefer() noexcept;

public:
  operation(prefix_unary_operator  op, operand&&  o) noexcept;
  operation(postfix_unary_operator  op, operand&&  o) noexcept;
  operation(binary_operator  op, operand&&  o1, operand&&  o2) noexcept;
  operation(const operation&   rhs) noexcept{*this = rhs;}
  operation(      operation&  rhs) noexcept{*this = std::move(rhs);}
 ~operation(){unrefer();}

  operation&  operator=(const operation&   rhs) noexcept;
  operation&  operator=(      operation&&  rhs) noexcept;

  bool  is_prefix_unary() const noexcept;
  bool  is_postfix_unary() const noexcept;
  bool  is_binary() const noexcept;

  value  evaluate(const execution_context*  ctx) const noexcept;

  void  print() const noexcept;

};


void  operate_prefix_unary( value&  v, operator_word  opw, const execution_context*  ctx) noexcept;
void  operate_postfix_unary(value&  v, operator_word  opw, const execution_context*  ctx) noexcept;
void  operate_binary(       value&  lv, value&  rv, operator_word  opw, const execution_context*  ctx) noexcept;
void  operate_stack(data_stack&  stack, const expr_element&  e, const execution_context*  ctx) noexcept;


class
data_stack
{
  static constexpr size_t  max_length = 32;

  value  m_switch_value;

  value  m_values[max_length];

  size_t  m_length=0;

public:

  void  push(value&&  v) noexcept{m_values[m_length++] = std::move(v);}

  value&  pop() noexcept{return m_values[--m_length];}

  void   load_switch_value() noexcept{push(value(m_switch_value));}
  void  store_switch_value() noexcept{m_switch_value = pop();}

  bool  compare_for_switch(const execution_context*  ctx) noexcept;

        value&  top()       noexcept{return m_values[m_length-1];}
  const value&  top() const noexcept{return m_values[m_length-1];}

  void  reset() noexcept{m_length = 0;}

  size_t  size() const noexcept{return m_length;}

};


class
expr_array
{
  class maker;

  struct data;

  data*  m_data=nullptr;

  void  read(script_token_cursor&  cur) noexcept;

  void  unrefer() noexcept;

public:
  expr_array() noexcept{}
  expr_array(gbstd::string_view  sv) noexcept;
  expr_array(script_token_cursor&  cur) noexcept{read(cur);}
  expr_array(const expr_array&   rhs) noexcept{*this = rhs;}
  expr_array(      expr_array&  rhs) noexcept{*this = std::move(rhs);}
 ~expr_array(){unrefer();}

  expr_array&  operator=(const expr_array&   rhs) noexcept;
  expr_array&  operator=(      expr_array&&  rhs) noexcept;

  value  evaluate(const execution_context*  ctx) const noexcept;

  expr_element*  begin() const noexcept;
  expr_element*    end() const noexcept;

  void  print() const noexcept;

};


class
operand
{
  enum class kind{
    null,
    boolean_literal,
    integer_literal,
    identifier,
    expression_array,
    operation,
  } m_kind=kind::null; 

  union data{
    bool  b;

    uint64_t  i;

    identifier  id;

    expr_array  ea;

    operation  op;

    data(){}
   ~data(){}

  } m_data;

public:
  operand() noexcept{}
  operand(bool  b) noexcept{*this = b;}
  operand(uint64_t  i) noexcept{*this = i;}
  operand(const identifier&  id) noexcept{*this = std::move(id);}
  operand(const expr_array&  e) noexcept{*this = e;}
  operand(const operation&  op) noexcept{*this = op;}
  operand(const operand&   rhs) noexcept{*this = rhs;}
  operand(      operand&&  rhs) noexcept{*this = std::move(rhs);}
 ~operand(){clear();}

  operand&  operator=(bool  b) noexcept;
  operand&  operator=(uint64_t  i) noexcept;
  operand&  operator=(const identifier&  id) noexcept;
  operand&  operator=(const expr_array&  e) noexcept;
  operand&  operator=(const operation&  op) noexcept;
  operand&  operator=(const operand&   rhs) noexcept;
  operand&  operator=(      operand&&  rhs) noexcept;


  void  clear() noexcept;

  bool  is_boolean_literal()   const noexcept{return m_kind == kind::boolean_literal;}
  bool  is_integer_literal()   const noexcept{return m_kind == kind::integer_literal;}
  bool  is_identifier()        const noexcept{return m_kind == kind::identifier;}
  bool  is_expression_array()  const noexcept{return m_kind == kind::expression_array;}
  bool  is_operation()         const noexcept{return m_kind == kind::operation;}

  bool               get_boolean_literal()  const noexcept{return m_data.b;}
  uint64_t           get_integer_literal()  const noexcept{return m_data.i;}
  const identifier&  get_identifier()       const noexcept{return m_data.id;}
  const expr_array&  get_expression_array() const noexcept{return m_data.ea;}
  const operation&   get_operation()        const noexcept{return m_data.op;}

  value  evaluate(const execution_context*  ctx) const noexcept;

  void  print() const noexcept;

};


class
expr_element
{
  enum class kind
  {
    null,
    operand,
    prefix_unary_operator,
    postfix_unary_operator,
    binary_operator,

  } m_kind=kind::null;

  union data{
    operand          o;
    operator_word  opw;

    data(){}
   ~data(){}

  } m_data;

public:
  expr_element(prefix_unary_operator  op) noexcept: m_kind(kind::prefix_unary_operator){m_data.opw = op.word;}
  expr_element(postfix_unary_operator  op) noexcept: m_kind(kind::postfix_unary_operator){m_data.opw = op.word;}
  expr_element(binary_operator  op) noexcept: m_kind(kind::binary_operator){m_data.opw = op.word;}
  expr_element(operand&&  o) noexcept: m_kind(kind::operand){new(&m_data) operand(std::move(o));}
  expr_element(const expr_element&   rhs) noexcept{*this = rhs;}
  expr_element(      expr_element&&  rhs) noexcept{*this = std::move(rhs);}
 ~expr_element(){clear();}

  expr_element&  operator=(const expr_element&   rhs) noexcept;
  expr_element&  operator=(      expr_element&&  rhs) noexcept;

  void  clear() noexcept;

  bool  is_prefix_unary_operator() const noexcept{return m_kind == kind::prefix_unary_operator;}
  bool  is_postfix_unary_operator() const noexcept{return m_kind == kind::postfix_unary_operator;}
  bool  is_binary_operator() const noexcept{return m_kind == kind::binary_operator;}
  bool  is_operand()  const noexcept{return m_kind == kind::operand;}

  operator_word  get_operator_word() const noexcept{return m_data.opw;}
  const operand&       get_operand() const noexcept{return m_data.o;}

};


}


using devices::expr_element;
using devices::expr_array;
using devices::operation;


}




#endif




