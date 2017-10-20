#ifndef GMBB_Script__Token_HPP
#define GMBB_Script__Token_HPP


#include<string>
#include<cstdio>
#include<new>
#include"gmbb_Script__TokenString.hpp"


namespace gmbb{
namespace script{


enum class
TokenKind
{
  null,
  punctuation,
  identifier,
  string,
  integer,
  token_string,

};


class Token;
class TokenString;


union
TokenData
{
  int                integer;
  std::string         string;
  TokenString*  token_string;

   TokenData(){}
  ~TokenData(){}

};


struct
Identifier
{
  std::string  string;

  Identifier(std::string&&  s) noexcept: string(std::move(s)){}

};


class
Token
{
  TokenKind  kind=TokenKind::null;
  TokenData  data;

public:
  Token() noexcept{}
  Token(int               i) noexcept: kind(TokenKind::integer     ){data.integer = i;}
  Token(std::string&&     s) noexcept: kind(TokenKind::string      ){new(&data) std::string(std::move(s));}
  Token(Identifier&&     id) noexcept: kind(TokenKind::identifier  ){new(&data) std::string(std::move(id.string));}
  Token(TokenString*   toks) noexcept: kind(TokenKind::token_string){data.token_string = toks;}
  Token(Token&&       rhs) noexcept{*this = std::move(rhs);}
  Token(Token const&  rhs) noexcept=delete;/*{*this = rhs;}*/
 ~Token(){clear();}

  Token&  operator=(Token&&       rhs) noexcept;
  Token&  operator=(Token const&  rhs) noexcept=delete;

  operator bool() const noexcept{return kind != TokenKind::null;}

  int                      get_integer() const noexcept{return data.integer;}
  std::string const&        get_string() const noexcept{return data.string;}
  TokenString const&  get_token_string() const noexcept{return *data.token_string;}

  bool  operator==(TokenKind  k) const noexcept{return kind == k;}

  TokenKind  get_kind() const noexcept{return kind;}

  void  clear() noexcept;

  void  print() const noexcept;

};


}}




#endif




