#ifndef LIBGBDN_stream_reader_HPP
#define LIBGBDN_stream_reader_HPP


#include"token.hpp"


namespace tok{
namespace tok_types{


class
stream_reader
{
  const char*  m_line_start;
  const char*  m_pointer;
  const char*  m_end;

  size_t  m_line_number=1;


  identifier  read_identifier() noexcept;
  punctuation_string  read_punctuation_string() noexcept;
  quoted_string  read_quoted_string(char  close_char) noexcept;

  unsigned int       read_binary_number() noexcept;
  unsigned int        read_octal_number() noexcept;
  unsigned int      read_decimal_number() noexcept;
  unsigned int  read_hexadecimal_number() noexcept;
  unsigned int  read_number_that_begins_by_zero() noexcept;

  void  skip_linestyle_comment();
  void  skip_blockstyle_comment();

  void  newline() noexcept;

public:
  stream_reader(std::string_view  sv) noexcept:
  m_line_start(sv.data()),
  m_pointer(sv.data()),
  m_end(sv.data()+sv.size()){}


  bool  is_reached_end() const noexcept{return !*m_pointer || (m_pointer >= m_end);}

  void  skip_spaces() noexcept;

  token  read_token();

};


}


using tok_types::stream_reader;


}




#endif




