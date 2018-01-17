#ifndef LIBGBSND_SCRIPT_HPP
#define LIBGBSND_SCRIPT_HPP


#include"libgbsnd/object.hpp"
#include"libtok/stream_reader.hpp"
#include<cstdio>


namespace gbsnd{
namespace devices{


template<typename  T>
inline T*
duplicate(T*  src) noexcept
{
  return src? new T(*src):nullptr;
}


class script_token;


class
operator_code
{
  char  m_data[4];

public:
  constexpr operator_code(char  c0=0, char  c1=0, char  c2=0, char  c3=0) noexcept: m_data{c0,c1,c2,c3}{}

  static constexpr operator_code  from_string_view(gbstd::string_view  sv) noexcept
  {
    return (sv.size() == 3)? operator_code(sv[0],sv[1],sv[2])
          :(sv.size() == 2)? operator_code(sv[0],sv[1])
          :(sv.size() == 1)? operator_code(sv[0])
          :operator_code();
  }

  constexpr const char*  get_string() const noexcept{return m_data;}

  constexpr operator uint32_t() const noexcept
  {
    return (m_data[0]<<24)|
           (m_data[1]<<16)|
           (m_data[2]<< 8);
  }

};


class
script_token_string
{
  script_token*  m_data=nullptr;

  size_t  m_length=0;

  char  m_open=0;
  char  m_close=0;

public:
  script_token_string() noexcept{}
  script_token_string(tok::stream_reader&  r, char  open, char  close);
  script_token_string(const script_token_string&   rhs) noexcept{*this = rhs;}
  script_token_string(      script_token_string&&  rhs) noexcept{*this = std::move(rhs);}
 ~script_token_string(){clear();}

  script_token_string&  operator=(const script_token_string&   rhs) noexcept;
  script_token_string&  operator=(      script_token_string&&  rhs) noexcept;

  void  clear() noexcept;

  size_t  size() const noexcept{return m_length;}

  const script_token*  data() const noexcept{return m_data;}

  char  get_open()  const noexcept{return m_open;}
  char  get_close() const noexcept{return m_close;}

  const script_token*  begin() const noexcept;
  const script_token*    end() const noexcept;

  void  print(FILE*  f, int  indent) const noexcept;

};


class
script_token
{
  enum class kind{
    null,
    identifier,
    integer_literal,
    operator_code,
    token_string,

  } m_kind=kind::null;

  union data{
    uint64_t  i;

    gbstd::string  id;

    operator_code  opco;

    script_token_string  toks;

    data(){}
   ~data(){}
  } m_data;

public:
  script_token() noexcept{}
  script_token(uint64_t  i) noexcept{*this = i;}
  script_token(gbstd::string&&  id) noexcept{*this = std::move(id);}
  script_token(const operator_code&  opco) noexcept{*this = opco;}
  script_token(script_token_string&&  toks) noexcept{*this = std::move(toks);}
  script_token(const script_token&   rhs) noexcept{*this = rhs;}
  script_token(      script_token&&  rhs) noexcept{*this = std::move(rhs);}
 ~script_token(){clear();}

  script_token&  operator=(uint64_t  i) noexcept;
  script_token&  operator=(gbstd::string&&  id) noexcept;
  script_token&  operator=(const operator_code&  opco) noexcept;
  script_token&  operator=(script_token_string&&  toks) noexcept;
  script_token&  operator=(const script_token&   rhs) noexcept;
  script_token&  operator=(      script_token&&  rhs) noexcept;

  void  clear() noexcept;

  bool  is_integer_literal()  const noexcept{return m_kind == kind::integer_literal;}
  bool  is_identifier()       const noexcept{return m_kind == kind::identifier;}
  bool  is_operator_code()    const noexcept{return m_kind == kind::operator_code;}
  bool  is_token_string()     const noexcept{return m_kind == kind::token_string;}

  uint64_t                    get_integer_literal()  const noexcept{return m_data.i;}
  const gbstd::string&        get_identifier()       const noexcept{return m_data.id;}
  const operator_code&        get_operator_code()    const noexcept{return m_data.opco;}
  const script_token_string&  get_token_string()     const noexcept{return m_data.toks;}

  void  print(FILE*  f, int  indent) const noexcept;

};


class
script
{
  std::vector<object>  m_object_list;

  script() noexcept{}

public:
  static script  build_from_string(gbstd::string_view  sv) noexcept;
  static script  build_from_file(gbstd::string_view  path) noexcept;
  static script  build_from_file(FILE*  f) noexcept;

};


}


using devices::script;


}




#endif




