#include"libgbsnd/script.hpp"
#include"libtok/stream_reader.hpp"


namespace gbsnd{
namespace devices{




script::
script(const script_token_string&  toks) noexcept
{
  script_token_cursor  cur(toks.begin(),toks.end());

    while(cur)
    {
      using sv = gbstd::string_view;

        if(cur[0].is_identifier() &&
           cur[1].is_identifier())
        {
          sv  type_name(cur[0].get_identifier().view());
          sv   var_name(cur[1].get_identifier().view());

          cur += 2;

            if(type_name == sv("square_wave"))
            {
              auto  sq = new square_wave;

              sq->set_name(var_name);

              m_square_wave_list.emplace_back(sq);

              m_object_list.emplace_back(var_name,value(*sq));
            }

          else
            if(type_name == sv("routine"))
            {
                if(cur[0].is_token_string('(',')') &&
                   cur[1].is_token_string('{','}'))
                {
                  auto&  parals = cur[0].get_token_string();
                  auto&   block = cur[1].get_token_string();

                  
                  auto  rt = new routine(parals,block);

                  m_object_list.emplace_back(var_name,value(*rt));

                  cur += 2;
                }
            }
        }

      else
        if(cur[0].is_semicolon())
        {
          cur += 1;
        }

      else
        {
          printf("不明な構文\n");

          break;
        }
    }
}




script
script::
build_from_string(gbstd::string_view  sv) noexcept
{
  tok::stream_reader  r(sv);

  script_token_string  toks(r,0,0);


  script  scr(toks);

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




