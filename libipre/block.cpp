#include"block.hpp"
#include"space.hpp"
#include"stmt.hpp"



namespace ipre{
namespace ipre_types{


void
block::
append(stmt*  st) noexcept
{
    if(st)
    {
        if(m_last)
        {
          m_last->set_next(st);
        }

      else
        {
          m_first = st;
        }


      m_last = st;

      ++m_number_of_statements;
    }
}


void
block::
read_struct_decl(tok::stream_reader&  r)
{
  std::string  name;

  r.skip_spaces();

    if(r.is_pointing_identifier())
    {
      name = r.read_identifier();

      r.skip_spaces();
    }


  ty::type_info  ti = ty::type_info::make_empty_struct();

  ty::type_decl  td(ti,name);

    if(r.get_char() == '{')
    {
      r.advance();

      r.skip_spaces();
    }
}


void
block::
build(tok::stream_reader&  r) noexcept
{
    for(;;)
    {
      r.skip_spaces();

        if(r.is_pointing_identifier())
        {
          auto&  name = r.read_identifier();

            if(name == std::string_view("struct"))
            {
              read_struct_decl(r);
            }
        }


    }
}




block::iterator&
block::iterator::
operator++() noexcept
{
  m_ptr = m_ptr->get_next();

  return *this;
}




}}




