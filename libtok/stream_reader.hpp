#ifndef stream_reader_HPP
#define stream_reader_HPP


#include<string>
#include<string_view>
#include<cstddef>
#include<cstdint>


namespace tok{
namespace tok_types{


class
stream_context
{
protected:
  const char*  m_line_start;
  const char*  m_pointer;
  const char*  m_end;

  size_t  m_line_number=1;

public:
  stream_context(std::string_view  sv) noexcept:
  m_line_start(sv.data()),
  m_pointer(sv.data()),
  m_end(sv.data()+sv.size()){}

  const char*  get_line_start() const noexcept{return m_line_start;}
  const char*  get_pointer() const noexcept{return m_pointer;}

  size_t  get_line_number() const noexcept{return m_line_number;}

  void  print() const noexcept
  {
    printf("[tok stream %4d行]\n",m_line_number);

    auto  p = m_line_start;

      while(p < m_pointer)
      {
        printf("%c",*p++);
      }


    printf("[_]\n");
  }

};


class
stream_reader: public stream_context
{
  std::string  m_string_buffer;

  uint64_t       read_binary_number() noexcept;
  uint64_t        read_octal_number() noexcept;
  uint64_t      read_decimal_number() noexcept;
  uint64_t  read_hexadecimal_number() noexcept;
  uint64_t  read_number_that_begins_by_zero() noexcept;

  void  skip_linestyle_comment() noexcept;
  void  skip_blockstyle_comment();

  void  newline() noexcept;

public:
  using stream_context::stream_context;


  stream_context  get_context() const noexcept{return *this;}

  const std::string&  read_identifier() noexcept;
  const std::string&  read_quoted_string(char  close_char) noexcept;

  uint64_t  read_number() noexcept;

  char  get_char() const noexcept{return *m_pointer;}

  void  advance() noexcept{++m_pointer;}

  bool  is_pointing_identifier() const noexcept;
  bool  is_pointing_number() const noexcept;

  bool  is_reached_end() const noexcept{return !*m_pointer || (m_pointer >= m_end);}

  void  skip_spaces();

};


}


using tok_types::stream_context;
using tok_types::stream_reader;


}




#endif




