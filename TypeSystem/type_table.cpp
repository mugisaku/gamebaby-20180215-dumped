#include"type_table.hpp"
#include<vector>
#include<new>


namespace ts{
namespace types{


namespace{




std::vector<const type_info*>
type_info_table({
  &s8_ti,
  &u8_ti,
  &s16_ti,
  &u16_ti,
  &s32_ti,
  &u32_ti,
  &bool_ti,
  &void_ti,
  &nullptr_ti,
  &geneptr_ti,
});


class
entry
{
  const type_info*  m_type_info;

  std::string  m_name;

public:
  entry() noexcept{}

  entry(const type_info&  info, std::string_view  name) noexcept:
  m_type_info(&info),
  m_name(name){}

  bool  operator==(std::string_view  name) const noexcept{return m_name == name;}


  const type_info&  get_type_info() const noexcept
  {
    return *m_type_info;
  }

  void  print(FILE*  f) const noexcept
  {
    fprintf(f,"name %s\n",m_name.data());

    get_type_info().print(f);
  }

};


std::vector<entry>
entry_table({
  entry( s8_ti,"int8_t"),
  entry( u8_ti,"uint8_t"),
  entry(s16_ti,"int16_t"),
  entry(u16_ti,"uint16_t"),
  entry(s32_ti,"int32_t"),
  entry(u32_ti,"uint32_t"),
  entry(   bool_ti,"bool"),
  entry(   void_ti,"void"),
  entry(nullptr_ti,"nullptr_t"),
  entry(geneptr_ti,"geneptr_t"),
});


}


const type_info        s8_ti("s8",   signed_integral_type_info(1));
const type_info        u8_ti("u8", unsigned_integral_type_info(1));
const type_info       s16_ti("s16",  signed_integral_type_info(2));
const type_info       u16_ti("u16",unsigned_integral_type_info(2));
const type_info       s32_ti("s32",  signed_integral_type_info(4));
const type_info       u32_ti("u32",unsigned_integral_type_info(4));
const type_info      bool_ti("b",boolean_type_info(1));
const type_info      void_ti( "v",void_type_info());
const type_info   nullptr_ti("np",pointer_type_info(pointer_kind::null));
const type_info   geneptr_ti("gp",pointer_type_info(pointer_kind::generic));


const type_info&
append_type_info(type_info&&  type_info) noexcept
{
    for(auto  ti: type_info_table)
    {
        if(ti->get_id() == type_info.get_id())
        {
          return *ti;
        }
    }


  auto  ti = new types::type_info(std::move(type_info));

  type_info_table.emplace_back(ti);

  return *ti;
}


void
name_type_info(const type_info&  type_info, std::string_view  name) noexcept
{
  entry_table.emplace_back(type_info,name);
}




const type_info&
get_type_info_by_name(std::string_view  name)
{
    for(auto&  ent: entry_table)
    {
        if(ent == name)
        {
          return ent.get_type_info();
        }
    }


  throw type_was_not_found();
}


const type_info&
get_type_info_by_id(std::string_view  id)
{
    for(auto  ti: type_info_table)
    {
        if(ti->get_id() == id)
        {
          return *ti;
        }
    }


  throw type_was_not_found();
}


void
print_all_types(FILE*  f) noexcept
{
  fprintf(f,"unnamed type_info{\n");

    for(auto  ti: type_info_table)
    {
      ti->print(f);

      fprintf(f,"\n");
    }


  fprintf(f,"}\n\nnamed type_info{\n");

    for(auto&  ent: entry_table)
    {
      ent.print(f);

      fprintf(f,"\n");
    }


  fprintf(f,"}\n\n");
}




}}





