#ifndef type_info_HPP
#define type_info_HPP


#include<cstddef>
#include<cstdint>
#include<cstdio>
#include<string>
#include<string_view>



namespace ts{
namespace types{


class
type_info
{
  uint32_t  m_index;

  std::string  m_name;
  std::string    m_id;

  size_t   m_size;
  size_t  m_align;

public:
  type_info() noexcept{}
  type_info(uint32_t  index, std::string_view  name, std::string_view  id, size_t  size, size_t  align) noexcept:
  m_index(index),
  m_name(name),
  m_id(id),
  m_size(size),
  m_align(align){}

  uint32_t  get_index() const noexcept{return m_index;}

  const std::string&  get_name() const noexcept{return m_name;}
  const std::string&    get_id() const noexcept{return   m_id;}

  size_t   get_size() const noexcept{return m_size;}
  size_t  get_align() const noexcept{return m_align;}

  void  print(FILE*  f=stdout) const noexcept
  {
    fprintf(f,"index<%8u>\n",m_index);
    fprintf(f," name %s\n",m_name.data());
    fprintf(f,"   id %s\n",m_id.data());
    fprintf(f," size %zu\n",m_size);
    fprintf(f,"align %zu\n",m_align);
  }

};


}


using types::type_info;


}


#endif




