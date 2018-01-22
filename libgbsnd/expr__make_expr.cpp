#include"libgbsnd/expr.hpp"
#include"libgbsnd/script.hpp"


namespace gbsnd{
namespace devices{


std::unique_ptr<expr>
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


enum class
operator_kind
{
  prefix_unary,
  postfix_unary,
  binary,

};


class
operator_egg
{
  operator_kind  m_kind;
  operator_word  m_word;

  int  m_precedence;

  bool  m_right_to_left;

public:
  constexpr operator_egg(operator_kind  k, operator_word  w, int  pred, bool  r2l=false) noexcept:
  m_kind(k),
  m_word(w),
  m_precedence(0xFF-pred),
  m_right_to_left(r2l){}


  constexpr bool  is_prefix_unary()  const noexcept{return m_kind == operator_kind::prefix_unary;}
  constexpr bool  is_postfix_unary() const noexcept{return m_kind == operator_kind::postfix_unary;}
  constexpr bool  is_binary()        const noexcept{return m_kind == operator_kind::binary;}

  constexpr int  precedence() const noexcept{return m_precedence;}

  constexpr bool  operator<(const operator_egg&  rhs) const noexcept{return m_precedence < rhs.m_precedence;}

  constexpr bool  is_right_to_left() const noexcept{return m_right_to_left;}

  expr*  create_expr() const noexcept
  {
    return is_prefix_unary() ? new expr( unary_operation( true,m_word))
          :is_postfix_unary()? new expr( unary_operation(false,m_word))
          :                    new expr(binary_operation(      m_word));
  }

};


class
postfix_note
{
  last  m_last;

  std::vector<std::unique_ptr<expr>>      m_expr_stack;
  std::vector<operator_egg>           m_operator_stack;

  void  transfer_operator() noexcept
  {
    m_expr_stack.emplace_back(m_operator_stack.back().create_expr());

    m_operator_stack.pop_back();
  }

public:
  void  push(operand&&  o) noexcept
  {
    m_expr_stack.emplace_back(new expr(std::move(o)));

    m_last.be_operand();
  }

  void  push(operator_egg  opeg) noexcept
  {
      while(m_operator_stack.size())
      {
        auto&  bk = m_operator_stack.back();

          if(bk < opeg)
          {
            break;
          }


        transfer_operator();
      }


    m_operator_stack.emplace_back(opeg);

    m_last.be_operator();
  }

  std::unique_ptr<expr>  make_expr() noexcept
  {
      while(m_operator_stack.size())
      {
        transfer_operator();
      }


    std::vector<std::unique_ptr<expr>>  buffer;

      for(auto&  e: m_expr_stack)
      {
          if(e->is_operand())
          {
            buffer.emplace_back(std::move(e));
          }

        else
          if(e->is_unary_operation())
          {
              if(buffer.size() < 1)
              {
                printf("単項演算の演算項が無い\n");

                return nullptr;
              }


            e->get_unary_operation().reset(buffer.back().release());

            buffer.back() = std::move(e);
          }

        else
          if(e->is_binary_operation())
          {
              if(buffer.size() < 2)
              {
                printf("二項演算の演算項が足りない\n");

                return nullptr;
              }


            auto  r = buffer.back().release();
                      buffer.pop_back();

            e->get_binary_operation().reset(buffer.back().release(),r);

            buffer.back() = std::move(e);
          }
      }


      if(buffer.size() != 1)
      {
        printf("出力結果が不正\n");

        return nullptr;
      }


    return std::move(buffer.front());
  }

};


std::unique_ptr<expr>
make_expr(script_token_cursor&  cur) noexcept
{
  postfix_note  note;

    while(cur)
    {
      auto&  tok = *cur++;

        if(tok.is_identifier())
        {
          note.push(operand(tok.get_identifier()));
        }

      else
        if(tok.is_integer_literal())
        {
          note.push(operand(tok.get_integer()));
        }

      else
        if(tok.is_operator_word())
        {
          using  oe = operator_egg;
          using  ok = operator_kind;

          auto  opw = tok.get_operator_word();

            if(opw == operator_word("++"))
            {
              note.push(oe(ok::prefix_unary,opw,0));
            }

          else
            if(opw == operator_word("--"))
            {
              note.push(oe(ok::prefix_unary,opw,0));
            }

          else if(opw == operator_word("*")){note.push(oe(ok::prefix_unary,opw,2,true));}
          else if(opw == operator_word("&")){note.push(oe(ok::prefix_unary,opw,2,true));}
          else if(opw == operator_word("!")){note.push(oe(ok::prefix_unary,opw,2,true));}
          else if(opw == operator_word("~")){note.push(oe(ok::prefix_unary,opw,2,true));}
          else if(opw == operator_word("-")){note.push(oe(ok::prefix_unary,opw,2,true));}

          else if(opw == operator_word(  "+")){note.push(oe(ok::binary,opw,5));}
          else if(opw == operator_word(  "-")){note.push(oe(ok::binary,opw,5));}
          else if(opw == operator_word(  "*")){note.push(oe(ok::binary,opw,4));}
          else if(opw == operator_word(  "/")){note.push(oe(ok::binary,opw,4));}
          else if(opw == operator_word(  "%")){note.push(oe(ok::binary,opw,4));}
          else if(opw == operator_word( "<<")){note.push(oe(ok::binary,opw,6));}
          else if(opw == operator_word( ">>")){note.push(oe(ok::binary,opw,6));}

          else if(opw == operator_word(  "|")){note.push(oe(ok::binary,opw,13));}
          else if(opw == operator_word(  "&")){note.push(oe(ok::binary,opw, 9));}
          else if(opw == operator_word(  "^")){note.push(oe(ok::binary,opw,10));}
          else if(opw == operator_word( "||")){note.push(oe(ok::binary,opw,11));}
          else if(opw == operator_word( "&&")){note.push(oe(ok::binary,opw,12));}

          else if(opw == operator_word( "==")){note.push(oe(ok::binary,opw,8));}
          else if(opw == operator_word( "!=")){note.push(oe(ok::binary,opw,8));}
          else if(opw == operator_word(  "<")){note.push(oe(ok::binary,opw,7));}
          else if(opw == operator_word( "<=")){note.push(oe(ok::binary,opw,7));}
          else if(opw == operator_word(  ">")){note.push(oe(ok::binary,opw,7));}
          else if(opw == operator_word( ">=")){note.push(oe(ok::binary,opw,7));}

          else if(opw == operator_word(  "=")){note.push(oe(ok::binary,opw,15,true));}
          else if(opw == operator_word( "+=")){note.push(oe(ok::binary,opw,15,true));}
          else if(opw == operator_word( "-=")){note.push(oe(ok::binary,opw,15,true));}
          else if(opw == operator_word( "*=")){note.push(oe(ok::binary,opw,15,true));}
          else if(opw == operator_word( "/=")){note.push(oe(ok::binary,opw,15,true));}
          else if(opw == operator_word( "%=")){note.push(oe(ok::binary,opw,15,true));}
          else if(opw == operator_word("<<=")){note.push(oe(ok::binary,opw,15,true));}
          else if(opw == operator_word(">>=")){note.push(oe(ok::binary,opw,15,true));}
          else if(opw == operator_word( "|=")){note.push(oe(ok::binary,opw,15,true));}
          else if(opw == operator_word( "&=")){note.push(oe(ok::binary,opw,15,true));}
          else if(opw == operator_word( "^=")){note.push(oe(ok::binary,opw,15,true));}
          else if(opw == operator_word(  ",")){note.push(oe(ok::binary,opw,16));}
          else if(opw == operator_word(  ".")){note.push(oe(ok::binary,opw, 1));}
          else if(opw == operator_word( "->")){note.push(oe(ok::binary,opw, 1));}
          else
            {
              printf("不明な演算子\n");
            }
        }

      else
        if(tok.is_semicolon())
        {
          break;
        }
    }


  return note.make_expr();
}



}}




