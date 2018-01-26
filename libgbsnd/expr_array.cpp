#include"libgbsnd/expr.hpp"
#include"libgbsnd/script.hpp"
#include<new>


namespace gbsnd{
namespace devices{




struct
expr_array::
data
{
  size_t  reference_count;

  size_t  number_of_elements;

  expr_element  elements[0];

};


expr_array::
expr_array(gbstd::string_view  sv) noexcept
{
  tok::stream_reader  r(sv);

  script_token_string  toks(r,0,0);

  script_token_cursor  cur(toks);

  read(cur);
}




expr_array&
expr_array::
operator=(const expr_array&  rhs) noexcept
{
    if(this != &rhs)
    {
      unrefer();

      m_data = rhs.m_data;

        if(m_data)
        {
          ++m_data->reference_count;
        }
    }


  return *this;
}


expr_array&
expr_array::
operator=(expr_array&&  rhs) noexcept
{
    if(this != &rhs)
    {
      unrefer();

      std::swap(m_data,rhs.m_data);
    }


  return *this;
}




void
expr_array::
unrefer() noexcept
{
    if(m_data)
    {
        if(!--m_data->reference_count)
        {
            for(auto&  e: *this)
            {
              gbstd::destruct(e);
            }


          free(m_data)         ;
               m_data = nullptr;
        }
    }
}


expr_element*  expr_array::begin() const noexcept{return &m_data->elements[0];}
expr_element*    expr_array::end() const noexcept{return begin()+m_data->number_of_elements;}




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
operator_egg
{
  enum class kind{
    prefix_unary,
    postfix_unary,
    binary,
  } m_kind;


  operator_word  m_word;

  int  m_precedence;

  bool  m_right_to_left;

public:
  constexpr operator_egg(prefix_unary_operator  op, int  pred, bool  r2l=false) noexcept:
  m_kind(kind::prefix_unary),
  m_word(op.word),
  m_precedence(0xFF-pred),
  m_right_to_left(r2l){}


  constexpr operator_egg(postfix_unary_operator  op, int  pred, bool  r2l=false) noexcept:
  m_kind(kind::postfix_unary),
  m_word(op.word),
  m_precedence(0xFF-pred),
  m_right_to_left(r2l){}


  constexpr operator_egg(binary_operator  op, int  pred, bool  r2l=false) noexcept:
  m_kind(kind::binary),
  m_word(op.word),
  m_precedence(0xFF-pred),
  m_right_to_left(r2l){}


  constexpr bool  is_prefix_unary()  const noexcept{return m_kind == kind::prefix_unary;}
  constexpr bool  is_postfix_unary() const noexcept{return m_kind == kind::postfix_unary;}
  constexpr bool  is_binary()        const noexcept{return m_kind == kind::binary;}

  constexpr int  precedence() const noexcept{return m_precedence;}

  constexpr bool  operator==(const operator_egg&  rhs) const noexcept{return m_precedence == rhs.m_precedence;}
  constexpr bool  operator< (const operator_egg&  rhs) const noexcept{return m_precedence <  rhs.m_precedence;}

  constexpr bool  is_right_to_left() const noexcept{return m_right_to_left;}

  expr_element  make_element() const noexcept
  {
    return is_prefix_unary() ? expr_element( prefix_unary_operator{m_word})
          :is_postfix_unary()? expr_element(postfix_unary_operator{m_word})
          :                    expr_element(       binary_operator{m_word});
  }

};


class
expr_array::
maker
{
  last  m_last;

  std::vector<expr_element>   m_element_stack;
  std::vector<operator_egg>  m_operator_stack;

  void  transfer_operator() noexcept
  {
    m_element_stack.emplace_back(m_operator_stack.back().make_element());

    m_operator_stack.pop_back();
  }

public:
  const last&  get_last() const noexcept{return m_last;}

  void  push(operand&&  o) noexcept
  {
    m_element_stack.emplace_back(std::move(o));

    m_last.be_operand();
  }

  void  push(operator_egg  opeg) noexcept
  {
      while(m_operator_stack.size())
      {
        auto&  bk = m_operator_stack.back();

          if(bk == opeg)
          {
              if(opeg.is_right_to_left())
              {
                break;
              }
          }

        else
          if(bk < opeg)
          {
            break;
          }


        transfer_operator();
      }


    m_operator_stack.emplace_back(opeg);

      if(opeg.is_binary())
      {
        m_last.be_operator();
      }
  }


  expr_array::data*  output() noexcept
  {
      while(m_operator_stack.size())
      {
        transfer_operator();
      }


    size_t  size = sizeof(expr_array::data)+(sizeof(expr_element)*m_element_stack.size());

    auto  ptr = static_cast<expr_array::data*>(malloc(size));

    ptr->reference_count    = 1;
    ptr->number_of_elements = m_element_stack.size();

    auto  src = m_element_stack.begin();

      for(int  i = 0;  i < m_element_stack.size();  ++i)
      {
        new(&ptr->elements[i]) expr_element(std::move(*src++));
      }


    return ptr;
  }

};


void
expr_array::
read(script_token_cursor&  cur) noexcept
{
  maker  mk;

    while(cur)
    {
      auto&  tok = *cur++;

        if(tok.is_identifier())
        {
          mk.push(operand(tok.get_identifier()));
        }

      else
        if(tok.is_integer_literal())
        {
          mk.push(operand(tok.get_integer()));
        }

      else
        if(tok.is_operator_word())
        {
          using  oe = operator_egg;

          using  preunop = prefix_unary_operator;
          using  posunop = postfix_unary_operator;
          using    binop = binary_operator;

          auto  opw = tok.get_operator_word();

            if(opw == operator_word("++"))
            {
              mk.push(oe(preunop{opw},0));
            }

          else
            if(opw == operator_word("--"))
            {
              mk.push(oe(preunop{opw},0));
            }

          else if(opw == operator_word("*"))
            {
              mk.push(mk.get_last().is_operand()? oe(  binop{opw},4     )
                                                : oe(preunop{opw},2,true));
            }
          else if(opw == operator_word("&")){mk.push(oe(preunop{opw},2,true));}
          else if(opw == operator_word("!")){mk.push(oe(preunop{opw},2,true));}
          else if(opw == operator_word("~")){mk.push(oe(preunop{opw},2,true));}
          else if(opw == operator_word("-")){mk.push(oe(preunop{opw},2,true));}

          else if(opw == operator_word(  "+")){mk.push(oe(binop{opw},5));}
          else if(opw == operator_word(  "-")){mk.push(oe(binop{opw},5));}
          else if(opw == operator_word(  "/")){mk.push(oe(binop{opw},4));}
          else if(opw == operator_word(  "%")){mk.push(oe(binop{opw},4));}
          else if(opw == operator_word( "<<")){mk.push(oe(binop{opw},6));}
          else if(opw == operator_word( ">>")){mk.push(oe(binop{opw},6));}

          else if(opw == operator_word(  "|")){mk.push(oe(binop{opw},13));}
          else if(opw == operator_word(  "&")){mk.push(oe(binop{opw}, 9));}
          else if(opw == operator_word(  "^")){mk.push(oe(binop{opw},10));}
          else if(opw == operator_word( "||")){mk.push(oe(binop{opw},11));}
          else if(opw == operator_word( "&&")){mk.push(oe(binop{opw},12));}

          else if(opw == operator_word( "==")){mk.push(oe(binop{opw},8));}
          else if(opw == operator_word( "!=")){mk.push(oe(binop{opw},8));}
          else if(opw == operator_word(  "<")){mk.push(oe(binop{opw},7));}
          else if(opw == operator_word( "<=")){mk.push(oe(binop{opw},7));}
          else if(opw == operator_word(  ">")){mk.push(oe(binop{opw},7));}
          else if(opw == operator_word( ">=")){mk.push(oe(binop{opw},7));}

          else if(opw == operator_word(  "=")){mk.push(oe(binop{opw},15,true));}
          else if(opw == operator_word( "+=")){mk.push(oe(binop{opw},15,true));}
          else if(opw == operator_word( "-=")){mk.push(oe(binop{opw},15,true));}
          else if(opw == operator_word( "*=")){mk.push(oe(binop{opw},15,true));}
          else if(opw == operator_word( "/=")){mk.push(oe(binop{opw},15,true));}
          else if(opw == operator_word( "%=")){mk.push(oe(binop{opw},15,true));}
          else if(opw == operator_word("<<=")){mk.push(oe(binop{opw},15,true));}
          else if(opw == operator_word(">>=")){mk.push(oe(binop{opw},15,true));}
          else if(opw == operator_word( "|=")){mk.push(oe(binop{opw},15,true));}
          else if(opw == operator_word( "&=")){mk.push(oe(binop{opw},15,true));}
          else if(opw == operator_word( "^=")){mk.push(oe(binop{opw},15,true));}
          else if(opw == operator_word(  ",")){mk.push(oe(binop{opw},16));}
          else if(opw == operator_word(  ".")){mk.push(oe(binop{opw}, 1));}
          else if(opw == operator_word( "->")){mk.push(oe(binop{opw}, 1));}
          else
            {
              printf("不明な演算子\n");
            }
        }

      else
        if(tok.is_token_string())
        {
          auto&  toks = tok.get_token_string();

            if((toks.get_open()  == '(') &&
               (toks.get_close() == ')'))
            {
              script_token_cursor  cocur(toks);

//              mk.push(operand(read_expr(cocur))));
            }

          else
            if((toks.get_open()  == '[') &&
               (toks.get_close() == ']'))
            {
            }

          else
            {
              printf("不明な字句列\n");
            }
        }

      else
        if(tok.is_semicolon())
        {
          break;
        }
    }


  m_data = mk.output();
}




value
expr_array::
evaluate(const execution_context&  ctx) const noexcept
{
}


void
expr_array::
print() const noexcept
{
    if(!m_data->number_of_elements)
    {
      return;
    }


  std::vector<operand>  buf;

    for(auto&  e: *this)
    {
        if(e.is_operand())
        {
          buf.emplace_back(e.get_operand());
        }

      else
        if(e.is_prefix_unary_operator())
        {
            if(buf.size() < 1)
            {
              printf("結果が不正\n");

              return;
            }


          operation  op(prefix_unary_operator{e.get_operator_word()},operand(buf.back()));

          buf.back() = std::move(op);
        }

      else
        if(e.is_postfix_unary_operator())
        {
            if(buf.size() < 1)
            {
              printf("結果が不正\n");

              return;
            }


          operation  op(postfix_unary_operator{e.get_operator_word()},operand(buf.back()));

          buf.back() = std::move(op);
        }

      else
        if(e.is_binary_operator())
        {
            if(buf.size() < 2)
            {
              printf("結果が不正\n");

              return;
            }


          operand  op2(std::move(buf.back()));

          buf.pop_back();

          operand  op1(std::move(buf.back()));

          operation  op(binary_operator{e.get_operator_word()},std::move(op1),std::move(op2));

          buf.back() = std::move(op);
        }
    }


    if(buf.size() != 1)
    {
      printf("結果が不正\n");

      return;
    }


  buf.front().print();
}


}}




