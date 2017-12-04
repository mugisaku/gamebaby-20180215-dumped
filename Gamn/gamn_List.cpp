#include"gamn_List.hpp"
#include"gamn_Value.hpp"
#include"gamn_StreamReader.hpp"
#include<cstring>




namespace gamn{


List::
List(StreamReader&  reader, char  cl)
{
  assign(reader,cl);
}


List::
List(const char*  filepath)
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

      StreamReader  sr(buf);

      assign(sr);

      delete[] buf;
    }

  else
    {
      printf("[gamn list construct error] %sを開けない",filepath);
    }
}




List&
List::
operator=(const List&  rhs) noexcept
{
  clear();

  auto  current = rhs.first;

    while(current)
    {
      push(Value(current->value));

      current = current->next;
    }


  return *this;
}


List&
List::
operator=(List&&  rhs) noexcept
{
  clear();

  std::swap(first,rhs.first);
  std::swap( last,rhs.last );

  number = rhs.number;

  return *this;
}




const Value*
List::
find_named_value(const char*  name) const noexcept
{
  auto  len = std::strlen(name);

    for(auto&  v: *this)
    {
        if(v.is_string() && v.get_string().compare(len,name))
        {
          return v.get_string().get_value();
        }
    }


  return nullptr;
}


const Value*
List::
access(std::initializer_list<const char*>  ls) const noexcept
{
  auto  it     = ls.begin();
  auto  it_end = ls.end();

  const Value*  v = nullptr;

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




void
List::
push(Value&&  v) noexcept
{
  auto  nd = new ListNode(std::move(v));

    if(last)
    {
      last->next = nd;
    }

  else
    {
      first = nd;
    }


  last = nd;

  ++number;
}


void
List::
assign(StreamReader&  reader, char  cl)
{
  clear();

  StreamContext  ctx;

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
          throw StreamError(reader,"}で閉じられていない");
        }

      else
        if(c == '}')
        {
          throw StreamError(reader,"余分な}");
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


          push(std::move(v));
        }
    }


  push(Value());
}


void
List::
clear() noexcept
{
  auto  current = first;

    while(current)
    {
      auto  next = current->next;

      delete current       ;
             current = next;
    }


  first = nullptr;
   last = nullptr;

  number = 0;
}


void
List::
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


}




