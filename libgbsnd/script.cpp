#include"libgbsnd/script.hpp"
#include"libtok/stream_reader.hpp"


namespace gbsnd{
namespace devices{




script
script::
build_from_string(gbstd::string_view  sv) noexcept
{
  tok::stream_reader  r(sv);

  script_token_string  toks(r,0,0);


  script  scr;

  return std::move(scr);
}


script
script::
build_from_file(gbstd::string_view  path) noexcept
{
  gbstd::string_copy  sc(path);

  auto  f = fopen(sc.data(),"rb");

    if(f)
    {
      auto  scr = build_from_file(f);

      fclose(f);

      return std::move(scr);
    }

  else
    {
      printf("%sを開けない\n",sc.data());
    }


  return script();
}


script
script::
build_from_file(FILE*  f) noexcept
{
  gbstd::string  s;

    for(;;)
    {
      auto  c = fgetc(f);

        if(feof(f) || ferror(f))
        {
          break;
        }


      s += c;
    }


  return build_from_string(s);
}




}}




