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
  std::list<Symbol>   entry_symbol_list;
  std::list<Symbol>   label_symbol_list;
  std::vector<std::string>  string_list;

  std::vector<Choosing>   choosing_list;

  class Element;

  Element*  first=nullptr;
  Element*   last=nullptr;

  uint32_t  append_string(const std::string&  s) noexcept;

  void  append_label_symbol(const std::string&  s) noexcept;
  void  append_entry_symbol(const std::string&  s) noexcept;

  Symbol&  get_label_symbol(const std::string&  s) noexcept;
  Symbol&  get_entry_symbol(const std::string&  s) noexcept;

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




