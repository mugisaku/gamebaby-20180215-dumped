#include"libgbsnd/script.hpp"
#include<vector>


namespace gbsnd{
namespace devices{




namespace{
struct
op
{
  gbstd::string_view  m_sv;

  operator_code  m_opco;

  constexpr op(gbstd::string_view  sv) noexcept:
  m_sv(sv),
  m_opco(operator_code::from_string_view(sv)){}

};


bool
try_push(tok::stream_reader&  r, op  op_, std::vector<script_token>&  buf) noexcept
{
    if(r.advance_if_matched(op_.m_sv))
    {
      buf.emplace_back(op_.m_opco);

      return true;
    }


  return false;
}
}


script_token_string::
script_token_string(tok::stream_reader&  r, char  open, char  close):
m_open(open),
m_close(close)
{
  std::vector<script_token>  buffer;

    for(;;)
    {
      r.skip_spaces();

        if(r.is_reached_end())
        {
            if(open)
            {
              printf("script_token_string error\n");
            }


          break;
        }


      auto  c = r.get_char();

        if(c == close)
        {
          r.advance();

          break;
        }

      else
        if(c == '(')
        {
          r.advance();

          buffer.emplace_back(script_token_string(r,'(',')'));
        }

      else
        if(c == '{')
        {
          r.advance();

          buffer.emplace_back(script_token_string(r,'{','}'));
        }

      else
        if(c == '[')
        {
          r.advance();

          buffer.emplace_back(script_token_string(r,'[',']'));
        }

      else
        if((c == ')') ||
           (c == '}') ||
           (c == ']'))
        {
          printf("script_token_string error\n");

          throw;
        }

      else if(try_push(r,gbstd::string_view("..."),buffer)){}
      else if(try_push(r,gbstd::string_view("."),buffer)){}
      else if(try_push(r,gbstd::string_view("++"),buffer)){}
      else if(try_push(r,gbstd::string_view("+="),buffer)){}
      else if(try_push(r,gbstd::string_view("+"),buffer)){}
      else if(try_push(r,gbstd::string_view("--"),buffer)){}
      else if(try_push(r,gbstd::string_view("->"),buffer)){}
      else if(try_push(r,gbstd::string_view("-="),buffer)){}
      else if(try_push(r,gbstd::string_view("-"),buffer)){}
      else if(try_push(r,gbstd::string_view("*="),buffer)){}
      else if(try_push(r,gbstd::string_view("*"),buffer)){}
      else if(try_push(r,gbstd::string_view("/="),buffer)){}
      else if(try_push(r,gbstd::string_view("/"),buffer)){}
      else if(try_push(r,gbstd::string_view("%="),buffer)){}
      else if(try_push(r,gbstd::string_view("%"),buffer)){}
      else if(try_push(r,gbstd::string_view("<<="),buffer)){}
      else if(try_push(r,gbstd::string_view("<<"),buffer)){}
      else if(try_push(r,gbstd::string_view("<="),buffer)){}
      else if(try_push(r,gbstd::string_view("<"),buffer)){}
      else if(try_push(r,gbstd::string_view(">>="),buffer)){}
      else if(try_push(r,gbstd::string_view(">>"),buffer)){}
      else if(try_push(r,gbstd::string_view(">="),buffer)){}
      else if(try_push(r,gbstd::string_view(">"),buffer)){}
      else if(try_push(r,gbstd::string_view("||"),buffer)){}
      else if(try_push(r,gbstd::string_view("|="),buffer)){}
      else if(try_push(r,gbstd::string_view("|"),buffer)){}
      else if(try_push(r,gbstd::string_view("&&"),buffer)){}
      else if(try_push(r,gbstd::string_view("&="),buffer)){}
      else if(try_push(r,gbstd::string_view("&"),buffer)){}
      else if(try_push(r,gbstd::string_view("^="),buffer)){}
      else if(try_push(r,gbstd::string_view("^"),buffer)){}
      else if(try_push(r,gbstd::string_view("=="),buffer)){}
      else if(try_push(r,gbstd::string_view("="),buffer)){}
      else if(try_push(r,gbstd::string_view("!="),buffer)){}
      else if(try_push(r,gbstd::string_view("!"),buffer)){}
      else if(try_push(r,gbstd::string_view("::"),buffer)){}
      else if(try_push(r,gbstd::string_view(":"),buffer)){}
      else if(try_push(r,gbstd::string_view(","),buffer)){}
      else if(try_push(r,gbstd::string_view("?"),buffer)){}
      else if(try_push(r,gbstd::string_view(";"),buffer)){}
      else
        if(r.is_pointing_identifier())
        {
          buffer.emplace_back(gbstd::string(r.read_identifier()));
        }

      else
        if(r.is_pointing_number())
        {
          buffer.emplace_back(r.read_number());
        }

      else
        {
          printf("処理できない文字です %d\n",c);

          break;
        }
    }


  m_length = buffer.size();

  m_data = new script_token[m_length+1];

  script_token*  p = m_data;

    for(auto&&  etok: buffer)
    {
      *p++ = std::move(etok);
    }
}




script_token_string&
script_token_string::
operator=(const script_token_string&  rhs) noexcept
{
  clear();

  m_data = new script_token[rhs.m_length];

  m_length = rhs.m_length;
  m_open   = rhs.m_open  ;
  m_close  = rhs.m_close ;

  std::copy(rhs.begin(),rhs.end(),m_data);


  return *this;
}


script_token_string&
script_token_string::
operator=(script_token_string&&  rhs) noexcept
{
  clear();

  std::swap(m_data  ,rhs.m_data  );
  std::swap(m_length,rhs.m_length);
  std::swap(m_open  ,rhs.m_open  );
  std::swap(m_close ,rhs.m_close );


  return *this;
}



void
script_token_string::
clear() noexcept
{
  delete[] m_data          ;
           m_data = nullptr;

  m_length = 0;

  m_open  = 0;
  m_close = 0;
}


const script_token*  script_token_string::begin() const noexcept{return m_data;}
const script_token*    script_token_string::end() const noexcept{return m_data+m_length;}


void
script_token_string::
print(FILE*  f, int  indent) const noexcept
{
    if(m_open)
    {
      fprintf(f,"%c",m_open);
    }


  auto  it     = begin();
  auto  it_end =   end();

    if(it != it_end)
    {
      it++->print(f,indent);

        while(it != it_end)
        {
          it++->print(f,indent);
        }
    }


    if(m_close)
    {
      fprintf(f,"%c",m_close);
    }
}


}}




