#ifndef token_HPP
#define token_HPP


#include<cstddef>
#include<string>
#include<new>


namespace tok{
namespace tok_types{


class
token_info
{
  const char*  m_line_start_pointer=nullptr;
  const char*     m_current_pointer=nullptr;

  size_t  m_line_number=0;

public:
  token_info() noexcept{}

  token_info(const char*  line_start_pointer, const char*  current_pointer, size_t  line_number) noexcept:
  m_line_start_pointer(line_start_pointer),
  m_current_pointer(current_pointer),
  m_line_number(line_number){}

  const char*  get_line_start_pointer() const noexcept{return m_line_start_pointer;}
  const char*  get_current_pointer() const noexcept{return m_current_pointer;}

  size_t  get_line_number() const noexcept{return m_line_number;}

};


struct
identifier
{
  std::string  m_content;

  identifier(std::string&&  content) noexcept:
  m_content(std::move(content)){}

};


struct
punctuation_string
{
  std::string  m_content;

  punctuation_string(std::string&&  content) noexcept:
  m_content(std::move(content)){}

};


struct
quoted_string
{
  std::string  m_content;

  quoted_string(std::string&&  content) noexcept:
  m_content(std::move(content)){}

};


class
token
{
  token_info  m_info;

  enum class kind{
    null,
    integer,
    quoted_string,
    identifier,
    punctuation_string,

  } m_kind=kind::null;

  union data{
    unsigned int  i;

    std::string  s;

    data(){}
   ~data(){}
  } m_data;


  void  clear() noexcept;

public:
  token() noexcept{}
  token(const token_info&  info, unsigned int  i) noexcept: m_info(info), m_kind(kind::integer){m_data.i = i;}
  token(const token_info&  info, identifier&&  id) noexcept: m_info(info), m_kind(kind::identifier){new(&m_data) std::string(std::move(id.m_content));}
  token(const token_info&  info, quoted_string&&  qs) noexcept: m_info(info), m_kind(kind::quoted_string){new(&m_data) std::string(std::move(qs.m_content));}
  token(const token_info&  info, punctuation_string&&  ps) noexcept: m_info(info), m_kind(kind::punctuation_string){new(&m_data) std::string(std::move(ps.m_content));}
  token(const token&   rhs) noexcept{*this = rhs;}
  token(      token&&  rhs) noexcept{*this = std::move(rhs);}
 ~token(){clear();}

  token&  operator=(const token&   rhs) noexcept;
  token&  operator=(      token&&  rhs) noexcept;

  operator bool() const noexcept{return m_kind != kind::null;}

  bool  is_integer()            const noexcept{return m_kind == kind::integer;}
  bool  is_identifier()         const noexcept{return m_kind == kind::identifier;}
  bool  is_quoted_string()      const noexcept{return m_kind == kind::quoted_string;}
  bool  is_punctuation_string() const noexcept{return m_kind == kind::punctuation_string;}

  const token_info&  get_info() const noexcept{return m_info;}

  unsigned int         get_integer() const noexcept{return m_data.i;}
  const std::string&   get_string()  const noexcept{return m_data.s;}

  void  print() const noexcept;

};


}


using tok_types::token;
using tok_types::token_info;


}




#endif




