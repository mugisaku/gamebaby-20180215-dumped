#include"gmbb_StreamWriter.hpp"
#include<cstdio>




namespace gmbb{




void
StreamWriter::
put(int  c) noexcept
{
    if(offset < stream->get_size())
    {
      stream->overwrite(c,offset);
    }

  else
    {
      stream->append(c);
    }


  offset += 1;
}


void
StreamWriter::
put_be16(int  c) noexcept
{
  put(c>>8);
  put(c   );
}


void
StreamWriter::
put_be32(int  c) noexcept
{
  put(c>>24);
  put(c>>16);
  put(c>> 8);
  put(c    );
}


}




