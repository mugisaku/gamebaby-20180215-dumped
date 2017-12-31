#ifndef GMBB_binary_Stream_HPP
#define GMBB_binary_Stream_HPP


#include<string>
#include<cstdint>
#include<cstddef>


namespace gbstd{
namespace binary_streams{


class binary_stream;




class
binary_stream_reader
{
  const char*    m_begin;
  const char*      m_end;
  const char*  m_current;

public:
  binary_stream_reader(std::string_view  sv) noexcept;

  void  rewind() noexcept{m_current = m_begin;}

  void  advance(size_t  n) noexcept{m_current += n;}

  int  get() noexcept;
  int  get_be16() noexcept;
  int  get_be32() noexcept;

  operator bool() const noexcept{return m_current < m_end;}

};


class
binary_stream_writer
{
  binary_stream*  m_stream;

  size_t  m_offset;

public:
  binary_stream_writer(binary_stream&  s, size_t  offset=0) noexcept:
  m_stream(&s),
  m_offset(offset){}

  void  put(int  c) noexcept;
  void  put_be16(int  c) noexcept;
  void  put_be32(int  c) noexcept;

  size_t  get_offset(         ) const noexcept{return m_offset    ;}
  void    set_offset(size_t  o)       noexcept{       m_offset = o;}

};


class
binary_stream
{
  std::string  m_content;

public:
  binary_stream() noexcept{}
  binary_stream(std::string&&  content) noexcept: m_content(std::move(content)){}


  void  overwrite(int  c, size_t  offset) noexcept{m_content[offset]  = c;}
  void     append(int  c                ) noexcept{m_content         += c;}

  const std::string*  operator->() const noexcept{return &m_content;}

  bool  set_content_from_file(std::string_view  path) noexcept;

  const std::string&  get_content() const noexcept{return m_content;}

  size_t  get_size() const noexcept{return m_content.size();}

  binary_stream_reader  make_reader() const noexcept{return binary_stream_reader(m_content);}
  binary_stream_writer  make_writer()       noexcept{return binary_stream_writer(*this);}

  void  output_content_to_file(std::string_view  path, bool  use_zlib=false) const noexcept;

};


}


using binary_streams::binary_stream;
using binary_streams::binary_stream_reader;
using binary_streams::binary_stream_writer;


}




#endif




