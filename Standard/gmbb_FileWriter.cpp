#include"gmbb_FileWriter.hpp"
#include<cstdio>




namespace gmbb{




FileWriter::
FileWriter() noexcept
{
}




void
FileWriter::
put(int  c) noexcept
{
    if(offset < content.size())
    {
      content[offset] = c;
    }

  else
    {
      content.push_back(c);
    }


  offset += 1;
}


void
FileWriter::
put_be16(int  c) noexcept
{
  put(c>>8);
  put(c   );
}


void
FileWriter::
put_be32(int  c) noexcept
{
  put(c>>24);
  put(c>>16);
  put(c>> 8);
  put(c    );
}


void
FileWriter::
put_file(const File&  f) noexcept
{
  put_be32(f.get_name().size());

    for(auto  c: f.get_name())
    {
      put(c);
    }


  put_be32(f->size());

    for(auto  c: f.get_content())
    {
      put(c);
    }
}


}




