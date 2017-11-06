#ifndef GMBB_FILEWRITER_HPP
#define GMBB_FILEWRITER_HPP


#include"gmbb_Stream.hpp"


namespace gmbb{


class
StreamWriter
{
  Stream*  stream;

  size_t  offset;

public:
  StreamWriter(Stream*  s=nullptr, size_t  offset_=0) noexcept: stream(s), offset(offset_){}

  void  put(int  c) noexcept;
  void  put_be16(int  c) noexcept;
  void  put_be32(int  c) noexcept;

  size_t  get_offset(         ) const noexcept{return offset    ;}
  void    set_offset(size_t  o)       noexcept{       offset = o;}

};


}




#endif




