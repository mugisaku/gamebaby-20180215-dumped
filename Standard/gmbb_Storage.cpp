#include"gmbb_Storage.hpp"
#include<cstdio>




namespace gmbb{




const File*
Storage::
find(const char*  filename) const noexcept
{
    for(auto&  f: file_table)
    {
        if(f.get_name() == filename)
        {
          return &f;
        }
    }


  return nullptr;
}




void
Storage::
load(const char*  path) noexcept
{
  file_table.clear();

  File  container(std::string(),File::get_content_from_file(path,true));

    if(container->size())
    {
      auto  r = container.make_reader();

      auto  n = r.get_be32();

        while(n--)
        {
          file_table.emplace_back(r);
        }
    }
}


void
Storage::
save(const char*  path) const noexcept
{
  FileWriter  w;

  w.put_be32(file_table.size());

    for(auto&  f: file_table)
    {
      w.put_file(f);
    }


  File::put_content_to_file(path,w.get_content(),true);
}


}




