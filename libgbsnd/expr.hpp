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

  value  evaluate(const execution_context&  ctx) const noexcept;

  expr_element*  begin() const noexcept;
  expr_element*    end() const noexcept;

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
    expression_array,
  } m_kind=kind::null; 

  union data{
    bool  b;

    uint64_t  i;

    identifier  id;

    expr_array  ea;

    data(){}
   ~data(){}

  } m_data;

public:
  operand() noexcept{}
  operand(undefined  u) noexcept{*this = u;}
  operand(bool  b) noexcept{*this = b;}
  operand(uint64_t  i) noexcept{*this = i;}
  operand(const identifier&  id) noexcept{*this = std::move(id);}
  operand(const expr_array&  e) noexcept{*this = e;}
  operand(const operand&   rhs) noexcept{*this = rhs;}
  operand(      operand&&  rhs) noexcept{*this = std::move(rhs);}
 ~operand(){clear();}

  operand&  operator=(undefined  u) noexcept;
  operand&  operator=(bool  b) noexcept;
  operand&  operator=(uint64_t  i) noexcept;
  operand&  operator=(const identifier&  id) noexcept;
  operand&  operator=(const expr_array&  e) noexcept;
  operand&  operator=(const operand&   rhs) noexcept;
  operand&  operator=(      operand&&  rhs) noexcept;


  void  clear() noexcept;

  bool  is_undefined_literal() const noexcept{return m_kind == kind::undefined_literal;}
  bool  is_boolean_literal()   const noexcept{return m_kind == kind::boolean_literal;}
  bool  is_integer_literal()   const noexcept{return m_kind == kind::integer_literal;}
  bool  is_identifier()        const noexcept{return m_kind == kind::identifier;}
  bool  is_expression_array()  const noexcept{return m_kind == kind::expression_array;}

  bool               get_boolean_literal()  const noexcept{return m_data.b;}
  uint64_t           get_integer_literal()  const noexcept{return m_data.i;}
  const identifier&  get_identifier()       const noexcept{return m_data.id;}
  expr_array         get_expression_array()       const noexcept{return m_data.ea;}

  value  evaluate(const execution_context&  ctx) const noexcept;

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


}




#endif




