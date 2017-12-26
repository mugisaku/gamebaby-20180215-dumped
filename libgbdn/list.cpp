#include"list.hpp"
#include"value.hpp"
#include"stream_reader.hpp"
#include<cstring>




namespace gbdn{
namespace gbdn_types{


list&
list::
operator=(const list&  rhs) noexcept
{
  clear();

  m_data = new value[rhs.size()];

  m_number_of_values = rhs.size();

  auto  p = m_data;

    for(auto&  v: rhs)
    {
      *p++ = v;
    }


  return *this;
}


list&
list::
operator=(list&&  rhs) noexcept
{
  clear();

  std::swap(m_data,rhs.m_data);

  m_number_of_values = rhs.size();

  return *this;
}




const value&
list::
get_named_value(const char*  name) const
{
  auto  v = find_named_value(name);

    if(!v)
    {
      throw value_was_not_found{name};
    }


  return *v;
}


const value*
list::
find_named_value(const char*  name) const noexcept
{
  const string_view  name_view(name);

    for(auto&  v: *this)
    {
        if(v.is_string() && (v.get_string() == name_view))
        {
          return v.get_string().get_value();
        }
    }


  return nullptr;
}


const value*
list::
access(std::initializer_list<const char*>  ls) const noexcept
{
  auto  it     = ls.begin();
  auto  it_end = ls.end();

  const value*  v = nullptr;

    if(it != it_end)
    {
      v = find_named_value(*it++);

        if(!v)
        {
          return nullptr;
        }


        while(it != it_end)
        {
            if(!v->is_list())
            {
              return nullptr;
            }


          v = v->get_list().find_named_value(*it++);

            if(!v)
            {
              return nullptr;
            }
        }
    }


  return v;
}




namespace{
class
buffer
{
  static constexpr size_t  initial_number = 256;

  value*  data;

  uint32_t  number_of_allocated;
  uint32_t  number_of_pushed=0;

public:
  buffer() noexcept: data(new value[initial_number]), number_of_allocated(initial_number){}
 ~buffer(){delete[] data;}

  uint32_t  get_number_of_pushed() const noexcept{return number_of_pushed;}

  value*  release_pointer() noexcept
  {
    auto  p = data          ;
              data = nullptr;

    return p;
  }

  void  push(value&&  v) noexcept
  {
      if(number_of_pushed >= number_of_allocated)
      {
        constexpr int  rate = 2;

        auto  new_data = new value[number_of_allocated*rate];

          for(int  i = 0;  i < number_of_pushed;  ++i)
          {
            new_data[i] = std::move(data[i]);
          }


        delete[] data           ;
                 data = new_data;

        number_of_allocated *= rate;
      }


    data[number_of_pushed++] = std::move(v);
  }

};
}


void
list::
assign(stream_reader&  reader, char  cl)
{
  clear();

  stream_context  ctx;

  buffer  buf;

    for(;;)
    {
      reader.skip_spaces();

      auto  c = reader.get_char();

        if(c == cl)
        {
          reader.advance(1);

          break;
        }

      else
        if(!c)
        {
          throw stream_error(reader,"}で閉じられていない");
        }

      else
        if(c == '}')
        {
          throw stream_error(reader,"余分な}");
        }

      else
        if(c == ',')
        {
          reader.advance(1);
        }

      else
        {
          ctx = reader;

          auto  v = reader.read_value();

            if(!v)
            {
              break;
            }


          buf.push(std::move(v));
        }
    }


  m_data = buf.release_pointer();

  m_number_of_values = buf.get_number_of_pushed();
}


void
list::
open(const char*  filepath)
{
  auto  f = fopen(filepath,"rb");

    if(f)
    {
      size_t  len = 0;

        for(;;)
        {
          fgetc(f);

            if(feof(f))
            {
              break;
            }


          ++len;
        }


      auto  buf = new char[len+1];

      auto  p = buf;

      rewind(f);

        while(len--)
        {
          *p++ = fgetc(f);
        }


      *p = 0;

      stream_reader  sr(buf);

      assign(sr);

      delete[] buf;
    }

  else
    {
      printf("[gbdn list construct error] %sを開けない",filepath);
    }
}


void
list::
clear() noexcept
{
  delete[] m_data          ;
           m_data = nullptr;

  m_number_of_values = 0;
}


void
list::
print(int  indent) const noexcept
{
  printf("{\n");

    for(auto&  v: *this)
    {
        for(int  n = 0;  n < indent;  ++n)
        {
          printf("  ");
        }


      v.print(indent+1);

      printf("\n");
    }


    if(indent)
    {
        for(int  n = 0;  n < indent-1;  ++n)
        {
          printf("  ");
        }
    }


  printf("}\n");
}


}}




