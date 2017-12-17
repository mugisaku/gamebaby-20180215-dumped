#include"type_table.hpp"
#include<vector>


namespace ts{
namespace type_tables{


namespace{


class
entry
{
  types::type*  m_type;

  type_info  m_type_info;

public:
  entry() noexcept{}

  entry(uint32_t  index, std::string_view  name, std::string_view  id, size_t  size, size_t  align) noexcept:
  m_type(nullptr),
  m_type_info(index,name,id,size,align){}

  entry(uint32_t  index, types::type*  type, std::string_view  name, std::string_view  id, size_t  size, size_t  align) noexcept:
  m_type(type),
  m_type_info(index,name,id,size,align){}

  bool  operator==(std::string_view  name) const noexcept{return m_type_info.get_name() == name;}

  const type&  get_type() const noexcept
  {
    return *m_type;
  }


  const type_info&  get_type_info() const noexcept
  {
    return m_type_info;
  }

  void  print(FILE*  f) const noexcept
  {
    get_type_info().print(f);

    fprintf(f,"\n");
  }

};


std::vector<entry>
table({
  entry(0, "int8_t","i8",1,1),
  entry(1,"uint8_t","u8",1,1),
  entry(2, "int8_t","i8",2,2),
  entry(3,"uint8_t","u8",2,2),
  entry(4, "int8_t","i8",4,4),
  entry(5,"uint8_t","u8",4,4),

  entry(6,     "void", "v",0,0),
  entry(7,"nullptr_t","np",4,4),
  entry(8,"geneptr_t","gp",4,4),

});


}


const type*
append_type(types::type*  type, std::string_view  name) noexcept
{
  char  buf[256];

  type->print_id(buf,sizeof(buf));

  std::string_view  id(buf);

  table.emplace_back(table.size(),type,name,id,0,0);

  return type;
}


const type&
get_type_by_name(std::string_view  name)
{
    for(auto&  ent: table)
    {
        if(ent == name)
        {
          return ent.get_type();
        }
    }


  throw type_was_not_found();
}


const type&
get_type_by_index(type_index  i)
{
  return table[i.get_value()].get_type();
}


const type_info&
get_type_info_by_name(std::string_view  name)
{
    for(auto&  ent: table)
    {
        if(ent == name)
        {
          return ent.get_type_info();
        }
    }


  throw type_was_not_found();
}


const type_info&
get_type_info_by_index(type_index  i)
{
  return table[i.get_value()].get_type_info();
}


void
print_all_types(FILE*  f) noexcept
{
    for(auto&  ent: table)
    {
      ent.print(f);
    }
}




}}





