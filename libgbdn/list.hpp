#ifndef LIBGBDN_LIST_HPP
#define LIBGBDN_LIST_HPP


#include"libtok/stream_reader.hpp"
#include<cstdint>


namespace gbdn{
namespace gbdn_types{


class value;


struct
value_was_not_found
{
  std::string_view  name;
  
};



class
list
{
  struct reader;

  value*  m_data=nullptr;

  uint32_t  m_number_of_values=0;

  value   read_number(tok::stream_reader&  r);
  value*  read_value_of_pair(tok::stream_reader&  r, char  cl);
  value   read_value(tok::stream_reader&  r, char  cl);

  list(tok::stream_reader&  reader, char  cl=0){assign(reader,cl);}

  void  assign(tok::stream_reader&  reader, char  cl=0);

public:
  list() noexcept{}
  list(const char*  filepath){open(filepath);}
  list(const list&   rhs) noexcept{*this = rhs;}
  list(      list&&  rhs) noexcept{*this = std::move(rhs);}
 ~list(){clear();}


  list&  operator=(const list&   rhs) noexcept;
  list&  operator=(      list&&  rhs) noexcept;

  void  clear() noexcept;

  uint32_t  size() const noexcept{return m_number_of_values;}

  void  open(const char*  filepath);

  const value&   get_named_value(std::string_view  name) const;
  const value*  find_named_value(std::string_view  name) const noexcept;
  const value*  access(std::initializer_list<const char*>  ls) const noexcept;

  void  print(int  indent=0) const noexcept;

  const value*  begin() const noexcept;
  const value*    end() const noexcept;

};


}


using gbdn_types::list;
using gbdn_types::value_was_not_found;


}




#endif




