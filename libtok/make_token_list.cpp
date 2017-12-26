#include"tok.hpp"
#include"stream_reader.hpp"


namespace tok{
namespace tok_types{




token_list
make_token_list_from_string(std::string_view  sv)
{
  stream_reader  r(sv);

  token_list  ls;

    try
    {
        for(;;)
        {
          r.skip_spaces();

            if(r.is_reached_end())
            {
              break;
            }


          ls.emplace_back(r.read_token());
        }
    }


    catch(const token_info&  ti)
    {
    }


  return std::move(ls);
}


token_list
make_token_list_from_file(const char*  path)
{
  auto  f = fopen(path,"rb");

    if(f)
    {
      auto  ls = make_token_list_from_file(f);

      fclose(f);

      return std::move(ls);
    }


  printf("%sを開けない\n",path);

  return token_list();
}


token_list
make_token_list_from_file(FILE*  f)
{
  std::string  s;

    for(;;)
    {
      auto  c = fgetc(f);

        if(feof(f) || ferror(f))
        {
          break;
        }


      s.push_back(c);
    }


  return make_token_list_from_string(s);
}




}}




