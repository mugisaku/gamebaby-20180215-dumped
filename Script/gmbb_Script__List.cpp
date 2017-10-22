#include"gmbb_Script__List.hpp"
#include"gmbb_Script__Value.hpp"
#include"gmbb_Script__StreamReader.hpp"




namespace gmbb{
namespace script{


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
}




void
List::
push(Value&&  v) noexcept
{
  auto  nd = new Node(std::move(v));

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

      auto  v = reader(this);

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


}}




