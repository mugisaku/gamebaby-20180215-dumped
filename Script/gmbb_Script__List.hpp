#ifndef GMBB_Script__List_HPP
#define GMBB_Script__List_HPP


#include"covered_ptr"
#include"gmbb_Script__Value.hpp"


namespace gmbb{
namespace script{


class StreamReader;


struct
ListNode
{
  Value  value;

  ListNode*  next=nullptr;

  ListNode(Value&&  v) noexcept: value(std::move(v)){}

};


class
List
{
  covered_ptr<List>  parent;

  ListNode*  first=nullptr;
  ListNode*   last=nullptr;

  uint32_t  number=0;

  char  opening=0;
  char  closing=0;

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

  void  push(Value&&  v) noexcept;

  void  clear() noexcept;

  uint32_t  size() const noexcept{return number;}

  ListNode const*  get_first() const noexcept{return first;}

  void  assign(StreamReader&  reader, covered_ptr<List>  parent_=nullptr, char  op=0, char  cl=0);

  Value const&  operator[](std::string const&  name) const;
  Value const&  operator[](ValueTag const&  tag) const;

  Value const*  find_by_name(std::string const&  name) const noexcept;

  char  get_opening() const noexcept{return opening;}
  char  get_closing() const noexcept{return closing;}

  void  print() const noexcept;

};


}}




#endif




