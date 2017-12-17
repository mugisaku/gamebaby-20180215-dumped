#include"type_table.hpp"
#include<vector>


namespace ts{
namespace type_tables{


namespace{


class
entry
{
  uint32_t  m_index;

  types::type*  m_type;

  std::string  m_name;
  std::string    m_id;

public:
  entry() noexcept{}
  entry(uint32_t  index, types::type*  type, std::string_view  name, std::string_view  id) noexcept:
  m_index(index),
  m_type(type),
  m_name(name.data(),name.size()),
  m_id(id.data(),id.size()){}

  bool  operator==(std::string_view  name) const noexcept{return m_name == name;}

  const type&  get_type() const noexcept
  {
    return *m_type;
  }


  type_info  get_type_info() const noexcept
  {
    return type_info(m_index,m_name,m_id,m_type->get_size(),m_type->get_align());
  }

  void  print(FILE*  f) const noexcept
  {
    get_type_info().print(f);

    fprintf(f,"\n");
  }

};


std::vector<entry>
table({
  entry(0,new type(simple_type(                    8)), "int8_t","i8"),
  entry(1,new type(simple_type(unsign_specifier(), 8)),"uint8_t","u8"),
  entry(2,new type(simple_type(                   16)), "int8_t","i8"),
  entry(3,new type(simple_type(unsign_specifier(),16)),"uint8_t","u8"),
  entry(4,new type(simple_type(                   32)), "int8_t","i8"),
  entry(5,new type(simple_type(unsign_specifier(),32)),"uint8_t","u8"),

  entry(6,new type(simple_type( 0)),"void","v"),
  entry(7,new type(simple_type(32)),"nullptr_t","np"),
  entry(8,new type(simple_type(32)),"geneptr_t","gp"),

});


}


const type*
append_type(types::type*  type, std::string_view  name) noexcept
{
  char  buf[256];

  type->print_id(buf,sizeof(buf));

  std::string_view  id(buf);

  table.emplace_back(table.size(),type,name,id);

  return type;
}


const type&
get_type(std::string_view  name)
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


type_info
find_type_info(std::string_view  name)
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


void
print_all_types(FILE*  f) noexcept
{
    for(auto&  ent: table)
    {
      ent.print(f);
    }
}




}}





