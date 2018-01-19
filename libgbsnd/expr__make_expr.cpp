#include"libgbsnd/expr.hpp"
#include"libgbsnd/script.hpp"


namespace gbsnd{
namespace devices{


expr
make_expr(gbstd::string_view  sv) noexcept
{
  tok::stream_reader  r(sv);

  script_token_string  toks(r,0,0);

  script_token_cursor  cur(toks);

  return make_expr(cur);
}


class
last
{
  enum class kind{
    null,
    operator_,
    operand,
  } m_kind=kind::null;

public:
  bool  is_operator() const noexcept{return m_kind == kind::operator_;}
  bool  is_operand()  const noexcept{return m_kind == kind::operand;}

  void  be_operator() noexcept{m_kind = kind::operator_;}
  void  be_operand()  noexcept{m_kind = kind::operand;}

};


class
postfix_note
{
  last  m_last;

  std::vector<expr>               m_expr_stack;
  std::vector<operator_word>  m_operator_stack;

public:
  void  push(operand&&  o) noexcept
  {
    m_expr_stack.emplace_back(std::move(o));

    m_last.be_operand();
  }

  void  push(operator_word  opw) noexcept
  {
    m_operator_stack.emplace_back(opw);

    m_last.be_operator();
  }

};


expr
make_expr(script_token_cursor&  cur) noexcept
{
  postfix_note  note;

    while(cur)
    {
      auto&  tok = *cur++;

        if(tok.is_identifier())
        {
//          note.push(operand(tok.get_identifier()));
        }

      else
        if(tok.is_integer_literal())
        {
          note.push(operand(tok.get_integer()));
        }

      else
        if(tok.is_operator_word())
        {
          note.push(tok.get_operator_word());
        }

      else
        if(tok.is_semicolon())
        {
          break;
        }
    }
}



}}




