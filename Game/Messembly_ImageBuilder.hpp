#ifndef GMBB_Messembly_ImageBuilder_HPP
#define GMBB_Messembly_ImageBuilder_HPP


#include"Messembly.hpp"
#include<string>
#include<list>
#include<vector>


namespace      gmbb{
namespace messembly{


class
ImageBuilder
{
public:
  struct MetaSymbol: public Symbol{
    uint32_t  index;

    MetaSymbol(const std::string&  name, uint32_t  i=0) noexcept:
    Symbol(name),
    index(i){}

  };


private:
  std::list<MetaSymbol>   entry_symbol_list;
  std::list<MetaSymbol>   label_symbol_list;
  std::vector<std::string>  string_list;

  std::vector<Choosing>   choosing_list;

  class Element;

  Element*  first=nullptr;
  Element*   last=nullptr;

  uint32_t  append_string(const std::string&  s) noexcept;

  void  append_label_symbol(const std::string&  s) noexcept;
  void  append_entry_symbol(const std::string&  s) noexcept;

  MetaSymbol&  get_label_symbol(const std::string&  s) noexcept;
  MetaSymbol&  get_entry_symbol(const std::string&  s) noexcept;

  void  push_element(Element*  e) noexcept;

  struct Status;

  void  push_choosing(const gamn::List&  ls, Status&  st) noexcept;
  void  push_value(const gamn::Value&  v, Status&  st) noexcept;

public:
  ~ImageBuilder(){clear();}

  void  clear() noexcept;

  void  push_entry(const std::string&  name, const gamn::List&  ls) noexcept;
  void  push_entry_list(const gamn::List&  ls) noexcept;

  void  finalize() noexcept;

  Image  build() const noexcept;

  void  print() const noexcept;

};



}}




#endif




