#ifndef GAMN_List_HPP
#define GAMN_List_HPP


#include"gamn_Value.hpp"
#include<cstdint>


namespace gamn{


class StreamReader;


struct
ListNode
{
  Value  value;

  ListNode*  next=nullptr;

  ListNode(Value&&  v) noexcept: value(std::move(v)){}

};


struct
value_was_not_found
{
  const char*  name;
  
};



class
List
{
  ListNode*  first=nullptr;
  ListNode*   last=nullptr;

  uint32_t  number=0;

public:
  List() noexcept{}
  List(StreamReader&  reader, char  cl=0){assign(reader,cl);}
  List(const char*  filepath){open(filepath);}
  List(const List&   rhs) noexcept{*this = rhs;}
  List(      List&&  rhs) noexcept{*this = std::move(rhs);}
 ~List(){clear();}


  List&  operator=(const List&   rhs) noexcept;
  List&  operator=(      List&&  rhs) noexcept;

  void  push(Value&&  v) noexcept;

  void  clear() noexcept;

  uint32_t  size() const noexcept{return number;}

  ListNode const*  get_first() const noexcept{return first;}

  void  open(const char*  filepath);
  void  assign(StreamReader&  reader, char  cl=0);

  const Value&   get_named_value(const char*  name) const;
  const Value*  find_named_value(const char*  name) const noexcept;
  const Value*  access(std::initializer_list<const char*>  ls) const noexcept;

  void  print(int  indent=0) const noexcept;


  class Iterator{
    ListNode const*  node;

  public:
    Iterator(ListNode const*  nd=nullptr) noexcept: node(nd){}

    operator bool() const noexcept{return node;}

    const Value&  operator*() const noexcept{return node->value;}

    bool  operator!=(const Iterator&  rhs) const noexcept{return(node != rhs.node);}

    Iterator&  operator++() noexcept
    {
      node = node->next;

      return *this;
    }

  };


  Iterator  begin() const noexcept{return Iterator(  first);}
  Iterator    end() const noexcept{return Iterator(nullptr);}

};


}




#endif




