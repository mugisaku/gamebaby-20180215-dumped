#include"gmbb_Script__Token.hpp"
#include"gmbb_Script__TokenString.hpp"




namespace gmbb{
namespace script{




Token&
Token::
operator=(Token&&  rhs) noexcept
{
  clear();

  std::swap(kind,rhs.kind);

    switch(kind)
    {
  case(TokenKind::null):
      break;
  case(TokenKind::identifier):
  case(TokenKind::string):
      new(&data) std::string(std::move(rhs.data.string));
      break;
  case(TokenKind::integer):
      data.integer = rhs.data.integer;
      break;
  case(TokenKind::token_string):
      data.token_string = rhs.data.token_string;
      break;
  case(TokenKind::punctuation):
      break;
    }


  return *this;
}


/*
Token&
Token::
operator=(Token const&  rhs) noexcept
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
  case(TokenKind::null):
      break;
  case(TokenKind::identifier):
  case(TokenKind::string):
      new(&data) std::string(rhs.data.string);
      break;
  case(TokenKind::integer):
      data.integer = rhs.data.integer;
      break;
  case(TokenKind::token_string):
      data.token_string = new TokenString(*rhs.data.token_string);
      break;
  case(TokenKind::punctuation):
      break;
    }


  return *this;
}
*/


void
Token::
clear() noexcept
{
    switch(kind)
    {
  case(TokenKind::null):
      break;
  case(TokenKind::identifier):
  case(TokenKind::string):
      data.string.~basic_string();
      break;
  case(TokenKind::integer):
      break;
  case(TokenKind::token_string):
      delete data.token_string;
      break;
  case(TokenKind::punctuation):
      break;
    }


  kind = TokenKind::null;
}


void
Token::
print() const noexcept
{
    switch(kind)
    {
  case(TokenKind::null):
      printf("(null_token)");
      break;
  case(TokenKind::identifier):
      printf("%s",data.string.data());
      break;
  case(TokenKind::string):
      printf("\"%s\"",data.string.data());
      break;
  case(TokenKind::integer):
      printf("%d",data.integer);
      break;
  case(TokenKind::token_string):
      data.token_string->print();
      break;
  case(TokenKind::punctuation):
      break;
    }
}




}}




