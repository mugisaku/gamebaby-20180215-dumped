#ifndef LIBGBDN_string_HPP
#define LIBGBDN_string_HPP


#include<cstddef>
#include<string_view>


namespace gbdn{
namespace gbdn_types{


class value;


class
string
{
  static char  null;

  char*  m_data=&null;

  size_t  m_length=0;

  value*  m_value=nullptr;

public:
  string() noexcept{}
  string(std::string_view  sv, value*  v=nullptr) noexcept{assign(sv,v);}
  string(const string&   rhs) noexcept{*this = rhs;}
  string(      string&&  rhs) noexcept{*this = std::move(rhs);}
 ~string(){clear();}

  string&  operator=(const string&   rhs) noexcept;
  string&  operator=(      string&&  rhs) noexcept;

  bool  operator==(std::string_view  sv) const noexcept;

  void  clear() noexcept;

  void  assign(std::string_view  sv, value*  v=nullptr) noexcept;

  const char*  get_data() const noexcept{return m_data;}
  size_t  get_length() const noexcept{return m_length;}

  std::string_view  get_view() const noexcept{return std::string_view(m_data,m_length);}

  const char*  begin() const noexcept{return m_data       ;}
  const char*    end() const noexcept{return m_data+m_length;}

  void          set_value(value*  v) noexcept;
  const value*  get_value() const noexcept{return m_value;}

  void  print(int  indent=0) const noexcept;

};


}


using gbdn_types::string;


}




#endif




