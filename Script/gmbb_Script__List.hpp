#ifndef GMBB_Script__List_HPP
#define GMBB_Script__List_HPP


#include"covered_ptr"
#include"gmbb_Script__Value.hpp"


namespace gmbb{
namespace script{


class StreamReader;


class
List
{
public:
  struct Node{
    Value  value;

    Node*  next=nullptr;

    Node(Value&&  v) noexcept: value(std::move(v)){}
  };


private:
  covered_ptr<List>  parent;

  Node*  first=nullptr;
  Node*   last=nullptr;

  uint32_t  number=0;

  char  opening=0;
  char  closing=0;

  void  push(Value&&  v) noexcept;

public:
  List() noexcept{}
  List(StreamReader&  reader, covered_ptr<List>  parent_=nullptr, char  op=0, char  cl=0)
  {assign(reader,parent_,op,cl);}
  List(char const*  filepath);
  List(List const&  rhs) noexcept{*this = rhs;}
  List(List&&       rhs) noexcept{*this = std::move(rhs);}
 ~List(){clear();}


  List&  operator=(List const&  rhs) noexcept;
  List&  operator=(List&&       rhs) noexcept;

  List const*  get_parent() const noexcept{return parent.get_const_raw_pointer();}

  void  clear() noexcept;

  uint32_t  size() const noexcept{return number;}

  Node const*  get_first() const noexcept{return first;}

  void  assign(StreamReader&  reader, covered_ptr<List>  parent_=nullptr, char  op=0, char  cl=0);

  char  get_opening() const noexcept{return opening;}
  char  get_closing() const noexcept{return closing;}

  void  print() const noexcept;

};


}}




#endif




