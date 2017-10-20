#ifndef GMBB_FILE_HPP
#define GMBB_FILE_HPP


#include<string>
#include"gmbb_FileReader.hpp"


namespace gmbb{


class
File
{
protected:
  std::string  name;

  std::string  content;

public:
  File() noexcept{}
  File(std::string&&  name_, std::string&&  content_) noexcept;
  File(FileReader&  r) noexcept;


  const std::string*  operator->() const noexcept{return &content;}

  void  change_name(std::string&&  new_name) noexcept{name = std::move(new_name);}

  const std::string&  get_name() const noexcept{return name;}
  const std::string&  get_content() const noexcept{return content;}

  FileReader  make_reader() const noexcept{return FileReader(content.data(),content.size());}

  static std::string  get_content_from_file(const char*  path, bool  use_zlib=false) noexcept;
  static void         put_content_to_file(  const char*  path, const std::string&  content, bool  use_zlib=false) noexcept;

};


}




#endif




