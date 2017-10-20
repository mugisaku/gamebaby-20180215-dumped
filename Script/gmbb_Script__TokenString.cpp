#include"gmbb_Script__TokenString.hpp"
#include"gmbb_Script__Token.hpp"
#include"gmbb_Script__StreamReader.hpp"




namespace gmbb{
namespace script{


TokenString::
TokenString(char const*  filepath)
{
  StreamReader  sr(make_string_from_file(filepath).data());

  assign(sr);
}




void
TokenString::
assign(StreamReader&  reader, covered_ptr<TokenString>  parent_, char  op, char  cl)
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

      auto  tok = reader(this);

        if(!tok)
        {
          break;
        }


      emplace_back(std::move(tok));
    }


  emplace_back();
}




void
TokenString::
print() const noexcept
{
    if(opening){printf("%c",opening);}


    for(auto&  tok: *this)
    {
      tok.print();

      printf(" ");
    }


    if(closing){printf("%c",closing);}
}


}}




