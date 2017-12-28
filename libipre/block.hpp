#ifndef block_HPP
#define block_HPP


#include"libty/ty.hpp"
#include"libtok/stream_reader.hpp"
#include<list>



namespace ipre{
namespace ipre_types{


class stmt;


class
block
{
  block*  m_parent=nullptr;

  stmt*  m_first=0;
  stmt*  m_last=0;

  size_t  m_number_of_statements=0;

  void  read_struct_decl(tok::stream_reader&  r);

public:
  block(block*  parent=nullptr) noexcept: m_parent(parent){}

  void  append(stmt*  st) noexcept;

   const block*  get_parent() const noexcept{return m_parent;}

  size_t  get_number_of_statements() const noexcept{return m_number_of_statements;}

  void  build(tok::stream_reader&  r) noexcept;

  class iterator{
    const stmt*  m_ptr;
  public:
    iterator(const stmt*  ptr=nullptr) noexcept: m_ptr(ptr){}

    const stmt&  operator*() const noexcept{return *m_ptr;}

    bool  operator!=(const iterator&  rhs) const noexcept{return m_ptr != rhs.m_ptr;}

    iterator&  operator++() noexcept;

  };


  iterator  begin() const noexcept{return iterator(m_first);}
  iterator    end() const noexcept{return iterator(       );}

};


}


using ipre_types::block;



}


#endif




