#ifndef GMBB_Script__TokenString_HPP
#define GMBB_Script__TokenString_HPP


#include<vector>
#include"covered_ptr"


namespace gmbb{
namespace script{


class Token;
class StreamReader;


class
TokenString: public std::vector<Token>
{
  covered_ptr<TokenString>  parent;

  char  opening=0;
  char  closing=0;

public:
  TokenString() noexcept{}
  TokenString(StreamReader&  reader, covered_ptr<TokenString>  parent_=nullptr, char  op=0, char  cl=0)
  {assign(reader,parent_,op,cl);}
  TokenString(char const*  filepath);

  TokenString const*  get_parent() const noexcept{return parent.get_const_raw_pointer();}

  void  assign(StreamReader&  reader, covered_ptr<TokenString>  parent_=nullptr, char  op=0, char  cl=0);

  char  get_opening() const noexcept{return opening;}
  char  get_closing() const noexcept{return closing;}

  void  print() const noexcept;

};


}}




#endif




