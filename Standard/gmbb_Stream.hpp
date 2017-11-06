#ifndef GMBB_Stream_HPP
#define GMBB_Stream_HPP


#include<string>
#include"gmbb_StreamReader.hpp"


namespace gmbb{


class
Stream
{
  std::string  content;

public:
  Stream() noexcept{}
  Stream(std::string&&  content_) noexcept: content(std::move(content_)){}
  Stream(StreamReader&  r) noexcept;


  void  overwrite(int  c, size_t  offset) noexcept{content[offset]  = c;}
  void     append(int  c                ) noexcept{content         += c;}

  const std::string*  operator->() const noexcept{return &content;}

  bool  set_content_from_file(const char*  path) noexcept;

  const std::string&  get_content() const noexcept{return content;}

  size_t  get_size() const noexcept{return content.size();}

  StreamReader  make_reader() const noexcept{return StreamReader(content.data(),content.size());}

  void  output_content_to_file(const char*  path, bool  use_zlib=false) const noexcept;

};


}




#endif




