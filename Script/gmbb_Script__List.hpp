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
  List(StreamReader&  reader, covered_ptr<List>  parent_=nullptr, char  op=0, char  cl=0);
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

  Value const&  get(ValueKind  kind, std::string const&  name) const;

  List const&           get_list(std::string const&  name) const{return get(ValueKind::list   ,name).get_list();}
  Value const&         get_value(std::string const&  name) const{return get(ValueKind::value  ,name).get_value();}
  std::string const&  get_string(std::string const&  name) const{return get(ValueKind::string ,name).get_string();}
  int                get_integer(std::string const&  name) const{return get(ValueKind::integer,name).get_integer();}
  double                get_real(std::string const&  name) const{return get(ValueKind::real   ,name).get_real();}

  Value const*  find_by_name(std::string const&  name) const noexcept;

  char  get_opening() const noexcept{return opening;}
  char  get_closing() const noexcept{return closing;}

  void  print() const noexcept;


  class Iterator{
    ListNode const*  node;

  public:
    Iterator(ListNode const*  nd=nullptr) noexcept: node(nd){}

    operator bool() const noexcept{return node;}

    Value const&  operator*() const noexcept{return node->value;}

    bool  operator!=(Iterator const&  rhs) const noexcept{return(node != rhs.node);}

    Iterator&  operator++() noexcept
    {
      node = node->next;

      return *this;
    }

  };


  Iterator  begin() const noexcept{return Iterator(  first);}
  Iterator    end() const noexcept{return Iterator(nullptr);}

};


}}




#endif




