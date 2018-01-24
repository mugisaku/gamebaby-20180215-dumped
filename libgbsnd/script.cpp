#include"libgbsnd/script.hpp"
#include"libtok/stream_reader.hpp"


namespace gbsnd{
namespace devices{




struct
script::
data
{
  size_t  reference_count=1;

  std::vector<square_wave*>  square_wave_list;
  std::vector<routine*>          routine_list;

  std::vector<object>  object_list;

};


script::
script(const script_token_string&  toks) noexcept:
m_data(new data)
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

              m_data->square_wave_list.emplace_back(sq);

              m_data->object_list.emplace_back(var_name,value(*sq));
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

                  m_data->object_list.emplace_back(var_name,value(*rt));

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




script&
script::
operator=(const script&   rhs) noexcept
{
  unrefer();

  m_data = rhs.m_data;

    if(m_data)
    {
      ++m_data->reference_count;
    }


  return *this;
}


script&
script::
operator=(script&&  rhs) noexcept
{
  unrefer();

  std::swap(m_data,rhs.m_data);


  return *this;
}




void
script::
unrefer() noexcept
{
    if(m_data)
    {
        if(!--m_data->reference_count)
        {
          delete m_data          ;
                 m_data = nullptr;
        }
    }
}




std::vector<routine*>&
script::
get_routine_list() const noexcept
{
  return m_data->routine_list;
}


std::vector<square_wave*>&
script::
get_square_wave_list() const noexcept
{
  return m_data->square_wave_list;
}




const routine*
script::
find_routine(gbstd::string_view  name) const noexcept
{
    for(auto&  obj: m_data->object_list)
    {
        if((obj.get_name() == name) && obj.get_value().is_routine())
        {
          return &obj.get_value().get_routine();
        }
    }


  return nullptr;
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




