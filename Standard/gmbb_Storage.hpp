#ifndef GMBB_Storage_HPP
#define GMBB_Storage_HPP


#include"gmbb_File.hpp"
#include"gmbb_FileWriter.hpp"
#include<vector>


namespace gmbb{


class
Storage
{
  std::vector<File>  file_table;

public:
  Storage() noexcept{}
  Storage(const char*  path) noexcept{load(path);}


  const std::vector<File>*  operator->() const noexcept{return &file_table;}

  void  append(File&&  f) noexcept{file_table.emplace_back(std::move(std::move(f)));}

  const File*  find(const char*  filename) const noexcept;

  void  load(const char*  path)       noexcept;
  void  save(const char*  path) const noexcept;

};


}




#endif




