#ifndef LIBGBDN_LIST_HPP
#define LIBGBDN_LIST_HPP


#include"value.hpp"
#include<cstdint>


namespace gbdn{


class stream_reader;
class list;


class
list_node
{
  friend class list;

  value  content_value;

  list_node*  next=nullptr;

  list_node(value&&  v) noexcept: content_value(std::move(v)){}

};


struct
value_was_not_found
{
  const char*  name;
  
};



class
list
{
  list_node*  first=nullptr;
  list_node*   last=nullptr;

  uint32_t  number=0;

public:
  list() noexcept{}
  list(stream_reader&  reader, char  cl=0){assign(reader,cl);}
  list(const char*  filepath){open(filepath);}
  list(const list&   rhs) noexcept{*this = rhs;}
  list(      list&&  rhs) noexcept{*this = std::move(rhs);}
 ~list(){clear();}


  list&  operator=(const list&   rhs) noexcept;
  list&  operator=(      list&&  rhs) noexcept;

  void  push(value&&  v) noexcept;

  void  clear() noexcept;

  uint32_t  size() const noexcept{return number;}

  list_node const*  get_first() const noexcept{return first;}

  void  open(const char*  filepath);
  void  assign(stream_reader&  reader, char  cl=0);

  const value&   get_named_value(const char*  name) const;
  const value*  find_named_value(const char*  name) const noexcept;
  const value*  access(std::initializer_list<const char*>  ls) const noexcept;

  void  print(int  indent=0) const noexcept;


  class iterator{
    list_node const*  node;

  public:
    iterator(list_node const*  nd=nullptr) noexcept: node(nd){}

    operator bool() const noexcept{return node;}

    const value&  operator*() const noexcept{return node->content_value;}

    bool  operator!=(const iterator&  rhs) const noexcept{return(node != rhs.node);}

    iterator&  operator++() noexcept
    {
      node = node->next;

      return *this;
    }

  };


  iterator  begin() const noexcept{return iterator(  first);}
  iterator    end() const noexcept{return iterator(nullptr);}

};


}




#endif




