#ifndef LIBGBDN_LIST_HPP
#define LIBGBDN_LIST_HPP


#include"value.hpp"
#include<cstdint>


namespace gbdn{


class stream_reader;


struct
value_was_not_found
{
  const char*  name;
  
};



class
list
{
  value*  m_data=nullptr;

  uint32_t  m_number_of_values=0;

public:
  list() noexcept{}
  list(stream_reader&  reader, char  cl=0){assign(reader,cl);}
  list(const char*  filepath){open(filepath);}
  list(const list&   rhs) noexcept{*this = rhs;}
  list(      list&&  rhs) noexcept{*this = std::move(rhs);}
 ~list(){clear();}


  list&  operator=(const list&   rhs) noexcept;
  list&  operator=(      list&&  rhs) noexcept;

  void  clear() noexcept;

  uint32_t  size() const noexcept{return m_number_of_values;}

  void  open(const char*  filepath);
  void  assign(stream_reader&  reader, char  cl=0);

  const value&   get_named_value(const char*  name) const;
  const value*  find_named_value(const char*  name) const noexcept;
  const value*  access(std::initializer_list<const char*>  ls) const noexcept;

  void  print(int  indent=0) const noexcept;

  const value*  begin() const noexcept{return m_data;}
  const value*    end() const noexcept{return m_data+m_number_of_values;}

};


}




#endif




