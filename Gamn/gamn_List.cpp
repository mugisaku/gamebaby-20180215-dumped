#include"gamn_List.hpp"
#include"gamn_Value.hpp"
#include"gamn_StreamReader.hpp"




namespace gamn{


List::
List(StreamReader&  reader, covered_ptr<List>  parent_, char  op, char  cl)
{
  assign(reader,parent_,op,cl);
}


List::
List(char const*  filepath)
{
  StreamReader  sr(make_string_from_file(filepath).data());

  assign(sr);
}




List&
List::
operator=(List const&  rhs) noexcept
{
  clear();

  auto  current = rhs.first;

    while(current)
    {
      push(Value(current->value));

      current = current->next;
    }


  opening = rhs.opening;
  closing = rhs.closing;

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

  opening = rhs.opening;
  closing = rhs.closing;

  return *this;
}


Value const&
List::
operator[](std::string const&  name) const
{
  auto  current = first;

    while(current)
    {
        if(current->value == name)
        {
          return current->value;
        }


      current = current->next;
    }


  throw 0;
}


Value const&
List::
operator[](ValueTag const&  tag) const
{
  auto  current = first;

    while(current)
    {
        if(current->value == tag)
        {
          return current->value;
        }


      current = current->next;
    }


  throw 0;
}




Value const&
List::
get(ValueKind  kind, std::string const&  name) const
{
    for(auto&  v: *this)
    {
        if((v == kind) && (v == name))
        {
          return v;
        }
    }


  throw 0;
}


Value const*
List::
find_by_name(std::string const&  name) const noexcept
{
  auto  current = first;

    while(current)
    {
        if(current->value == name)
        {
          return &current->value;
        }


      current = current->next;
    }


  return nullptr;
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
assign(StreamReader&  reader, covered_ptr<List>  parent_, char  op, char  cl)
{
  clear();

  parent = parent_;

  opening = op;
  closing = cl;

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
        if((c == ')') ||
           (c == '}') ||
           (c == ']') ||
           (c == ',') ||
           (c == ';'))
        {
          throw StreamError(reader,"%cで閉じられている",c);
        }


      ctx = reader;

      auto  v = reader.read_value(this);

        if(!v)
        {
          break;
        }


      push(std::move(v));
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

  opening = 0;
  closing = 0;

  parent = nullptr;
}


void
List::
print() const noexcept
{
    if(opening){printf("%c",opening);}


  auto  current = first;

    while(current)
    {
      current->value.print();

      current = current->next;

      printf(" ");
    }


    if(closing){printf("%c",closing);}
}


}




