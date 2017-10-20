#ifndef GMBB_FILEWRITER_HPP
#define GMBB_FILEWRITER_HPP


#include"gmbb_File.hpp"


namespace gmbb{


class
FileWriter: public File
{
  size_t  offset;

public:
  FileWriter() noexcept;


  void  put(int  c) noexcept;
  void  put_be16(int  c) noexcept;
  void  put_be32(int  c) noexcept;

  void  put_file(const File&  f) noexcept;

};


}




#endif




